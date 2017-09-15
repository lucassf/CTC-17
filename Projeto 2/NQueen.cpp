#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ctime>
using namespace std;
#define MAXN 25

int N;

//Structure that contains information about a board:
//queen position and value
struct board{
private:
    bool canAttack(int l1,int l2,int col1,int col2){
        return l1==l2||col1==col2||abs(col1-col2)==abs(l1-l2);
    }
    //Calculate board value given the queen's position
    void setValue(){
        value = (N*(N+1))/2;

        int l1,l2;

        for (int i=0;i<N;i++){
            l1 = rows[i];
            for (int j=i+1;j<N;j++){
                l2 = rows[j];
                if (l1==l2||j-i==abs(l2-l1))value--;
            }
        }
    }
public:
    int value;
    int rows[MAXN];

    //Creates board randomly and calculates its value
    board(){
        for (int i=0;i<N;i++)rows[i] = rand()%N;
        setValue();
    }

    //Create board given previous board value and queen positioning
    board(board other,int col,int newrow){
        for (int i=0;i<N;i++)rows[i] = other.rows[i];
        rows[col] = newrow;
        value = other.value;
        for (int i=0;i<N;i++){
            if (i==col)continue;
            if (!canAttack(other.rows[i],other.rows[col],i,col))value--;
            if (!canAttack(rows[i],newrow,i,col))value++;
        }
    }

    //Operators
    bool operator >(board other)const{
        return value>other.value;
    }

    bool operator <(board other)const{
        return value<other.value;
    }

    ~board(){free(rows);}
};

//Print state of the board. 1 represents a queen.
void printState(board b){
    char str[MAXN][MAXN+1];
    memset(str,'0',sizeof str);

    printf("Solution board\n\n");

    for (int i=0;i<N;i++){
        str[b.rows[i]][i] = '1';
        str[i][N] = 0;
    }for (int i=0;i<N;i++)printf("%s\n",str[i]);
    printf("h = %d\n\n",b.value);
}

//Hill Climbing function
bool hillClimbing(board &initial){

    board current,next,aux;
    int row,bestcnt,MAXVALUE = (N*(N+1))/2;

    current = initial;

    while (true){
        bestcnt = 0;
        for (int i=0;i<N;i++){
            row = current.rows[i];
            for (int j=0;j<N;j++){
                if (j==row)continue;
                aux = board(current,i,j);
                if (next<aux)next = aux,bestcnt = 1;
            }
        }
        if (bestcnt == 0)break;
        current = next;
    }
    initial = current;
    return current.value == MAXVALUE;
}

//Main
int main(){
    board solution = board();
    srand(time(NULL));

    printf("Board Size: ");
    scanf("%d",&N);
    if (N<=3)N = 4;
    if (N>25)N=MAXN;

    const clock_t begin_time = clock();

    while (!hillClimbing(solution)){solution = board();}

    const clock_t end_time = clock();

    printState(solution);
    printf("CPU execution time: %.3lf\n\n",double( end_time - begin_time ) /  CLOCKS_PER_SEC);
    printf("Press Enter\n");
    char c;
    scanf("%c%c",&c,&c);
    return 0;
}
