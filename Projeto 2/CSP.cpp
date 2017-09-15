#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;


/*Each variable must have an empty value or one value contained in the domain.
In this case, the domain are the numbers from 0 to 4 (the houses) and -1
represents an empty value*/
class variable {
private:
    string name;
    int value;
public:
    variable(string name){
        static int acum_id = 0;
        this->name = name;
        value = -1;
    }

    string getName(){
        return name;
    }

    int getValue(){
        return value;
    }

    void setValue(int value){
        this->value = value;
    }

    void print(){
        cout<<name<<": "<<value<<endl;
    }
};

/*Define the constraints between all the variables. The value of adjList defines the constraint:
adjList[u][v] = 0 (No constraint), 1 (Same value), 2 (Different value), 3 (val[u] and val[v] adjacent),
4 (val[u] = val[v]+1), 5 (val[u] = val[v]-1)*/

class constraints{
private:
    vector<vector<int> > adjList;
    int N;
public:
    constraints(int N){
        if (N<=0)N = 1;

        this->N = N;
        adjList.assign(N,vector<int>());
        for (int i=0;i<N;i++)adjList[i].assign(N,0);
    }
    void addConstraint(int u,int v,int value){
        if (u<0||v<0||u>=N||v>=N)return;
        adjList[u][v] = value;
    }
    int getConstraint(int u,int v){
        return adjList[u][v];
    }
    void print(){
        for (int i=0;i<(int)adjList.size();i++){
            for (int j=0;j<(int)adjList[i].size();j++){
                cout<<adjList[i][j]<<" ";
            }cout<<endl;
        }
    }
};

/*Abstract class that contains the domains, variables and constraints. Some methods are
virtual, allowing them to be changed depending on the problem.*/
class csp {
protected:
    int N_variables;
    vector<variable> vars;
    constraints *constr;
public:
    virtual bool verifyConstraints(int u,int value) = 0;
    virtual bool isComplete(int var) = 0;
    virtual bool isAssigned(int var) = 0;
    virtual int domainSize(int var) = 0;
    virtual int getDomainValue(int var,int pos) = 0;
    virtual void removeVariableValue(int var) = 0;

    csp(vector<string> var_name){
        N_variables = var_name.size();
        for (int i=0;i<N_variables;i++){
            vars.push_back(variable(var_name[i]));
        }
        constr = new constraints(N_variables);
    }

    void addConstraint(int u,int v,int value){
        constr->addConstraint(u,v,value);
    }

    bool setVariableValue(int u,int value){
        if (u<0||u>=vars.size())return false;
        bool ok = verifyConstraints(u,value);
        if (ok) vars[u].setValue(value);

        return ok;
    }
    void printConst(){
        constr->print();
    }

    void printVariables(){
        for (int i=0;i<vars.size();i++){
            vars[i].print();
        }
        cout<<endl;
    }

    ~csp(){
        free(constr);
    }
};

/*Class that inherits from class csp. Contains methods to create variables and
constraints of the problem*/
class csp_problem:public csp{
private:
public:
    csp_problem(vector<string> vars):csp(vars){
    }
    bool verifyConstraints(int u,int uval){
        bool ret;
        for (int v=0;v<N_variables;v++){
            int cond = constr->getConstraint(u,v);
            int vval = vars[v].getValue();
            if (v==u||vval == -1)continue;
            ret = true;

            switch(cond){
                case 1:
                    ret = vval==uval;
                    break;
                case 2:
                    ret = vval!=uval;
                    break;
                case 3:
                    ret = abs(vval-uval) == 1;
                    break;
                case 4:
                    ret = uval==vval+1;
                    break;
                case 5:
                    ret = uval==vval-1;
            }
            if (!ret)return false;
        }
        return true;
    }

    bool isComplete(int var){
        return var == N_variables;
    }

    bool isAssigned(int var){
        return vars[var].getValue()!=-1;
    };

    int domainSize(int var){
        return 5;
    }

    int getDomainValue(int var,int pos){
        return pos;
    }

    void removeVariableValue(int var){
        vars[var].setValue(-1);
    };
};




/*Method for adding the csp constraints*/
void addConstraints(csp_problem &problem){
    //Elements that must be in different houses
    for (int i=0;i<5;i++){
        for (int j=5*i;j<5*(i+1);j++){
            for (int k=5*i;k<5*(i+1);k++){
                problem.addConstraint(j,k,2);
            }
        }
    }
    //Elements that must be in the same house
    problem.addConstraint(0,5,1);
    problem.addConstraint(5,0,1);
    problem.addConstraint(15,4,1);
    problem.addConstraint(15,4,1);
    problem.addConstraint(17,6,1);
    problem.addConstraint(6,17,1);
    problem.addConstraint(10,9,1);
    problem.addConstraint(9,10,1);
    problem.addConstraint(13,16,1);
    problem.addConstraint(16,13,1);
    problem.addConstraint(14,3,1);
    problem.addConstraint(3,14,1);
    problem.addConstraint(23,1,1);
    problem.addConstraint(1,23,1);
    problem.addConstraint(22,12,1);
    problem.addConstraint(12,22,1);

    //Elements that must be in adjacent houses
    problem.addConstraint(2,7,3);
    problem.addConstraint(7,2,3);
    problem.addConstraint(21,11,3);
    problem.addConstraint(11,21,3);
    problem.addConstraint(24,10,3);
    problem.addConstraint(10,24,3);
    problem.addConstraint(6,8,4);
    problem.addConstraint(8,6,5);

    //Two variables have its value already set by the problem. Add them!
    problem.setVariableValue(2,0);
    problem.setVariableValue(18,2);
}

/*Method for creating the csp variables*/
csp_problem build_csp(){
    int N_variables = 25;
    string names[N_variables] = {
        "INGLES","ESPANHOL","NORUEGUES","JAPONES","UCRANIANO",
        "VERMELHO","VERDE","AZUL","MARFIM","AMARELO",
        "KOOL","CHESTERFIELD","WINSTON","LUCKYSTRIKE","PARLIAMENT",
        "CHA","SUCO","CAFE","LEITE","AGUA",
        "ZEBRA","RAPOSA","CARAMUJO","CACHORRO","CAVALO"
        };
    vector<string> vars(names,names+N_variables);

    csp_problem problem(vars);
    addConstraints(problem);
    return problem;
}

/*Backtrack algorithm for the CSP*/
bool recursiveBacktrack(csp &problem, int var){
    if (problem.isComplete(var))return true;
    if (problem.isAssigned(var))return recursiveBacktrack(problem,var+1);

    int M = problem.domainSize(var);

    for (int i=0;i<M;i++){
        int value = problem.getDomainValue(var,i);

        if (problem.verifyConstraints(var,value)){
            problem.setVariableValue(var,value);
            if (recursiveBacktrack(problem,var+1))return true;
            problem.removeVariableValue(var);
        }
    }
    return false;
}

int main(){
    csp_problem problem = build_csp();
    if (recursiveBacktrack(problem,0))problem.printVariables();
    else cout<<"Failure"<<endl;
    cout<<"Press Enter"<<endl;
    char c;
    scanf("%c",&c);
    return 0;
}

