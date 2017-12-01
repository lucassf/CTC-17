#include <bits/stdc++.h>
using namespace std;
#define INF 1e9

const int NMAX = 100;
const int BOARDSIZE = 8;
const int MAXLOOPS = 10000;
const int MAXTIME = 100;
const double C = 1.494;
const double W = 0.8;
const double CR = 0.73423;

int NPARTICLES;

inline int fitness(int *queens){
    int f = BOARDSIZE*(BOARDSIZE - 1)/2, q1, q2;

    for (int i = 0; i < BOARDSIZE; i++){
        q1 = queens[i];
        for (int j = i + 1; j < BOARDSIZE; j++){
            q2 = queens[j];
            if (q1 == q2 || abs(q2 - q1) == abs(j - i))continue;
            f--;
        }
    }
    return f;
}

inline int randomPos(){
    return rand() % BOARDSIZE;
}

inline double randomVel(){
    return (2*BOARDSIZE*((double)rand()/RAND_MAX)) - BOARDSIZE;
}

inline void updateBest(int *arr, int *best){
    for (int i = 0; i < BOARDSIZE; i++){
        best[i] = arr[i];
    }
}

inline int PSO(){
    int x[NMAX][BOARDSIZE];
    double v[NMAX][BOARDSIZE];
    double vmax = BOARDSIZE;
    int p[NMAX][BOARDSIZE], fp[NMAX];
    int g[BOARDSIZE], fg;
    int iter = 0;

    for (int i = 0; i < NPARTICLES; i++){
        for (int j = 0; j < BOARDSIZE; j++){
            x[i][j] = randomPos();
            v[i][j] = randomVel();
        }
        fp[i] = INF;
    }
    fg = INF;

    for (int m = 0; m < MAXLOOPS && fg; m++){
        for (int i = 0; i < NPARTICLES; i++){
            int f = fitness(x[i]);
            if (f < fp[i]){
                fp[i] = f;
                copy(x[i], x[i] + NPARTICLES, p[i]);
            }
            if (f < fg){
                fg = f;
                copy(x[i], x[i] + NPARTICLES, g);
            }
        }
        for (int i = 0; i < NPARTICLES; i++){
            for (int j = 0; j < BOARDSIZE; j++){
                double r1 = (double)rand() / RAND_MAX;
                double r2 = (double)rand() / RAND_MAX;
                v[i][j] = W * v[i][j] + C * (r1 * (p[i][j] - x[i][j]) +
                        r2 * (g[j] - x[i][j]));
                if (v[i][j] > BOARDSIZE)v[i][j] = BOARDSIZE;
                if (v[i][j] < -BOARDSIZE)v[i][j] = -BOARDSIZE;
                x[i][j] = ((int)(v[i][j] + x[i][j]) % BOARDSIZE + BOARDSIZE) % BOARDSIZE;
            }
        }
        iter++;
    }
    return iter;
}

inline int DE(){
    int x[NMAX][BOARDSIZE];
    int u[BOARDSIZE], fg, f, iter;
    double v[BOARDSIZE], F;

    for (int i = 0; i < NPARTICLES; i++){
        for (int j = 0; j < BOARDSIZE; j++){
            x[i][j] = randomPos();
        }
    }
    fg = INF, iter = 0;

    for (int m = 0; m < MAXLOOPS && fg; m++){
        iter++;
        for (int i = 0; i < NPARTICLES; i++){
            int r1 = rand() % NPARTICLES;
            int r2 = rand() % NPARTICLES;
            int r3 = rand() % NPARTICLES;

            F = 0.5 * (1 + (double)rand() / RAND_MAX);

            for (int j = 0; j < BOARDSIZE; j++){
                v[j] = x[r1][j] + F * (x[r2][j] - x[r3][j]);
            }

            int n = rand() % BOARDSIZE;
            int L = 0;

            while (L < BOARDSIZE){
                int j = (n + L) % BOARDSIZE;
                u[j] = (((int)v[j]) % BOARDSIZE + BOARDSIZE) % BOARDSIZE;
                L++;
                if ((double)rand()/RAND_MAX >= CR)break;
            }
            while (L < BOARDSIZE){
                int j = (n + L++) % BOARDSIZE;
                u[j] = x[i][j];
            }
            f = fitness(u);
            if (f < fitness(x[i])){
                copy(u, u + BOARDSIZE, x[i]);
                if (f < fg)fg = f;
            }
        }
    }
    return iter;
}

void test(int (*f)(void)){
    int iter, val, sol;
    double t;

    for (NPARTICLES = 10; NPARTICLES <= NMAX; NPARTICLES+=10){
        iter = sol = 0;
        t = 0;
        clock_t begin_time = clock();
        for (int i = 0; i < MAXTIME; i++){
            val = (*f)();
            if (val != MAXLOOPS){
                sol++;
                iter += val;
            }
        }
        printf("Teste %d: %d %.10lf %.10lf\n", NPARTICLES/10,sol,(double)iter/MAXTIME,
               double( clock () - begin_time ) / (CLOCKS_PER_SEC / 1000) / MAXTIME);
    }
}

int main(){
    srand(time(NULL));

    printf("PSO:\n\n");
    test(PSO);
    printf("\nDE:\n\n");
    test(DE);

    return 0;
}
