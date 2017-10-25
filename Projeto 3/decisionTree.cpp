#include <bits/stdc++.h>
using namespace std;
#define MAXUSER 6100
#define MAXMOVIES 4000

/*User, movie and rating structures*/
struct user{
    int id,age,occupation,gender;
    string zipcode;

	user(){}
	user(int _id,int _age,int _occupation,int _gender,string _zipcode){
		id = _id,age = _age,occupation = _occupation;
		gender = _gender,zipcode = _zipcode;
	}
};

struct movie{
    int id;
    string title;
    int genres;

	movie(){}
	movie(int _id,string _title,int _genres){
		id = _id, title = _title, genres = _genres;
	}
};

struct rating{
    int score,id_movie,id_user;
    string timestamp;

	rating(){}
	rating(int _score,int _id_movie,int _id_user,string _timestamp){
		score = _score,id_movie = _id_movie,id_user = _id_movie;
		timestamp = _timestamp;
	}
};

/*Global variables*/
vector<user> users;
vector<movie> movies;
vector<rating> ratings;
set<int> attrValues[4];
int sortAttr;

/*File parsing begin*/
inline int getAgeRank(int age){
    if (age<18)return 0;
    if (age<25)return 1;
    if (age<35)return 2;
    if (age<45)return 3;
    if (age<50)return 4;
    if (age<56)return 5;
    return 6;
}
string genres[18] = {"Action","Adventure","Animation","Children's","Comedy","Crime","Documentary",
"Drama","Fantasy","Film-Noir","Horror","Musical","Mystery","Romance","Sci-Fi","Thriller","War","Western"};

inline vector<string> splitString(char *str){
    vector<string> ans;
    char s[100];
    int n = strlen(str),k=0;

    for (int i=0;i<n-1;i++){
        if (str[i]==':'&&str[i+1]==':'){
            s[k] = 0;
            ans.push_back(string(s));
            k = 0,i++;
        }
        else if (str[i]=='|'){
            s[k] = 0;
            ans.push_back(s);
            k = 0;
        }
        else s[k++]=str[i];
    }
    s[k] = 0;
    ans.push_back(string(s));
    return ans;
}

inline int getGenreRank(vector<string> &names){
    int mask = 0;
    int j;
    for (int i=0;i<names.size();i++){
        for (j=0;j<18;j++){
            if (names[i]==genres[j])break;
        }
        mask|=1<<j;
    }
    return mask;
}

inline void setUsers(vector<user> &users){
    FILE* user_input = fopen("users.dat","r");
    char aux[101];
    vector<string> parsed;
    user u;

    while (fgets(aux,100,user_input)){
        parsed = splitString(aux);

        u.id = atoi(parsed[0].c_str());
        u.gender = parsed[1]=="M"?0:1;
        u.age = getAgeRank(atoi(parsed[2].c_str()));
        u.occupation = atoi(parsed[3].c_str());
        u.zipcode = parsed[4];

        users.push_back(u);
    }
}

inline void setMovies(vector<movie> &movies){
    FILE* movies_input = fopen("movies.dat","r");
    char aux[101];
    int cur;
    vector<string> g;
    vector<string> parsed;
    movie u;

    while (fgets(aux,100,movies_input)){
        parsed = splitString(aux);
        g.clear();
        u.id = atoi(parsed[0].c_str());
        u.title = parsed[1];
        for (int i=2;i<parsed.size();i++)g.push_back(parsed[i]);
        u.genres = getGenreRank(g);
        movies.push_back(u);
    }
}

inline void setRatings(vector<rating> &ratings){
    FILE* ratings_input = fopen("ratings.dat","r");
    char aux[101];
    vector<string> parsed;
    rating u;

    while (fgets(aux,100,ratings_input)){
        parsed = splitString(aux);
        u.id_user = atoi(parsed[0].c_str());
        u.id_movie = atoi(parsed[1].c_str());
        u.score = atoi(parsed[2].c_str());
        u.timestamp = parsed[3];

        ratings.push_back(u);
    }
}
/*File parsing end*/

/*Decision tree node (can be a leaf)*/
struct node{
    int attribute,score;
    vector<node*> adjList;
    vector<int> value;

    node(){}
    node(int attribute){
        this->attribute = attribute;
    }
    node(int attribute,int score){
        this->attribute = attribute;
        this->score = score;
    }
};

/*Decision tree*/
struct decisionTree{
    node* root;

    decisionTree(){root = NULL;}

    void printTree(){
        recursivePrint(root,0);
    }

    ~decisionTree(){
        node* aux = root;
        recursiveRemove(root);
    }

	int getScore(user u,movie m){
		node* curNode = root;
		while (curNode!=NULL && curNode->attribute!=-1){
			int attr = curNode->attribute;
			int v;
			if (attr==0)v = u.age;
			else if (attr==1)v = u.gender;
			else if (attr==2)v = u.occupation;
			else v = m.genres;

			for (int i=0;i<curNode->value.size();i++){
				if (curNode->value[i] == v){
					curNode = curNode->adjList[i];
					break;
				}
			}
		}
		if (curNode!=NULL)return curNode->score;
		return 0;
	}
private:
    void recursiveRemove(node* n){
        for (int i=0;i<(int)n->adjList.size();i++){
            recursiveRemove(n->adjList[i]);
        }
        free(n);
    }

    void recursivePrint(node* cur,int depth){
        if (cur==NULL)return;
        for (int i=0;i<depth;i++)printf(" ");
        if (cur->attribute==-1)printf("score: %d\n",cur->score);
        else printf("%d\n",cur->attribute);
        for (int i=0;i<(int)cur->adjList.size();i++){
            for (int j=0;j<depth;j++)printf(" ");
            printf("%d\n",cur->value[i]);
            recursivePrint(cur->adjList[i],depth+1);
        }
    }


};

/*Comparator function used to sort the ratings*/
bool compareRatings(rating a,rating b){
    if (sortAttr==0)return users[a.id_user-1].age<users[b.id_user-1].age;
    else if (sortAttr==1)return users[a.id_user-1].gender<users[b.id_user-1].gender;
    else if (sortAttr==2)return users[a.id_user-1].occupation<users[b.id_user-1].occupation;
    return movies[a.id_movie-1].genres<movies[b.id_movie-1].genres;
}

/*Returns the classification if all ratings have same score*/
int sameClassification(vector<rating> &ratings){
    user u;
    int score = -1;
    for (int i=0;i<ratings.size();i++){
        if (score!=-1 && score!= ratings[i].score)return -1;
        score = ratings[i].score;
    }
    return score;
}

/*Return the score that most appears in the ratings*/
int majorityScore(vector<rating> &ratings){
    int qtt[6] = {};
    int wmax,ans;

    for (int i=0;i<ratings.size();i++){
        qtt[ratings[i].score]++;
    }wmax = ans = 0;
    for (int i=0;i<=5;i++){
        if (qtt[i]>wmax)wmax=qtt[i], ans = i;
    }
    return ans;
}

/*Returns the value of an certain rating's attribute*/
inline int getAttributeValue(rating ratings,int attr){
    if (attr==0)return users[ratings.id_user-1].age;
    else if (attr==1)return users[ratings.id_user-1].gender;
    else if (attr==2)return users[ratings.id_user-1].occupation;
    return movies[ratings.id_movie-1].genres;
}

/*Calculates entropy for a list of ratings*/
inline double entropy(vector<rating> &ratings){
    int score[6] = {};
    for (int i=0;i<ratings.size();i++){
        score[ratings[i].score]++;
    }double sum = 0;
    int N = ratings.size();
    for(int i=0;i<=5;i++){
        if (score[i]==0)continue;
        sum-=(double)score[i]/N*log((double)score[i]/N);
    }
    return sum/N;
}

/*Choose an attribute which has larger information gain*/
int chooseAttribute(vector<int> &attributes,vector<rating> &ratings){
    if (attributes.size()==1)return attributes[0];
    vector<rating> nextRatings;

    double best_gain = 1,current_gain;
    int index = 0;

    for (int j=0;j<(int)attributes.size();j++){
        sortAttr = attributes[j];
        current_gain = 1;
        sort(ratings.begin(),ratings.end(),compareRatings);

        for (int i=0;i<(int)ratings.size();){
            int v = getAttributeValue(ratings[i],sortAttr);
            nextRatings.clear();
            while (i<(int)ratings.size()&&v==getAttributeValue(ratings[i],sortAttr))
                nextRatings.push_back(ratings[i++]);
            current_gain += entropy(nextRatings)*nextRatings.size();
        }
        current_gain/=ratings.size();
        if (current_gain<best_gain){
            best_gain = current_gain;
            index = j;
        }
    }
    return attributes[index];
}

/*Main function to create decision tree*/
inline node* createDecisionTree(vector<int> &attributes,vector<rating> &ratings,int score){
    int s = sameClassification(ratings);
    node* curNode;

    if (ratings.empty())curNode = new node(-1,score);
    else if (s!=-1)curNode = new node(-1,s);
    else if (attributes.empty())curNode = new node(-1,majorityScore(ratings));
    else{
        int bestAttr = chooseAttribute(attributes,ratings);
        sortAttr = bestAttr;
        int m = majorityScore(ratings);
        curNode = new node(bestAttr);

        vector<int> nextAttr;
        vector<rating> nextRatings;
        for (int i=0;i<attributes.size();i++)
            if (attributes[i]!=bestAttr)nextAttr.push_back(attributes[i]);
        sort(ratings.begin(),ratings.end(),compareRatings);

        for (int i=0;i<ratings.size();){
            nextRatings.clear();
            int v = getAttributeValue(ratings[i],bestAttr);
            while (i<ratings.size()&&v==getAttributeValue(ratings[i],bestAttr))
                nextRatings.push_back(ratings[i++]);
            curNode->adjList.push_back(createDecisionTree(nextAttr,nextRatings,m));
            curNode->value.push_back(v);
        }
    }
    return curNode;
}

/*Function main*/
int main(){
    setUsers(users);
    setMovies(movies);
    setRatings(ratings);

    decisionTree dT;
    vector<int> attributes = vector<int>(4);

    cout<<"Building tree"<<endl;
    for (int i=0;i<attributes.size();i++)attributes[i] = i;
    dT.root = createDecisionTree(attributes,ratings,0);

	cout<<"Finished building"<<endl;
	int age,gender,idmovie;
	string zipcode;
	user u(-1,1,4,0,"1231231");
	while (cin>>idmovie){
        cout<<dT.getScore(u,movies[idmovie-1])<<endl;
	}
}
