#include <cmath>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <ctime>
using namespace std;
#define EPS 1e-9
#define INF 1e9

//Generates a random value in range (rmin,rmax)
double randomRangeValue(double rmin,double rmax){
    if (rmax<=rmin)return 0;

    return ((double)rand()/(RAND_MAX))*(rmax-rmin)+rmin;
}


//State of the problem.
struct state{
public:
    double x,y;

    state(){
        x = randomRangeValue(-10,10);
        y = randomRangeValue(-10,10);
    }

    state(double _x,double _y){
        x = _x, y = _y;
    }

    double getValue(){
        return 4*exp(-(x*x+y*y))+exp(-((x-5)*(x-5)+(y-5)*(y-5)))+
        exp(-((x+5)*(x+5)+(y-5)*(y-5)))+exp(-((x-5)*(x-5)+(y+5)*(y+5)))+
        exp(-((x+5)*(x+5)+(y+5)*(y+5)));
    }

    void show(){
        printf("x = %.3lf, y = %.3lf, f(x,y) = %.3lf\n",x,y,getValue());
    }
};

state getNextState(state current){
    double x = randomRangeValue(-10,10);
    double y = randomRangeValue(-10,10);

    return state(x,y);
}

//Simulated Annealing function
void simulatedAnnealing(){
    double T,dE,cost,alpha,nextcost;
    state current,next;
    int MAX_TRIES = 100;

    alpha = 0.98;
    T = 100;

    while (true){
        if (abs(T)<EPS)break;

        current.show();
        for (int i=0;i<MAX_TRIES;i++){
            next = getNextState(current);
            dE = next.getValue() - current.getValue();


            double prob = exp(dE/T);
            if (dE>0||double(rand())/RAND_MAX<prob){
                current = next;
                break;
            }
        }
        T*=alpha;
    }
    printf("fmax = %.3lf\n",current.getValue());
}

int main(){
    srand(time(NULL));
    simulatedAnnealing();

    printf("Press Enter\n");
    char c;
    scanf("%c",&c);
}
