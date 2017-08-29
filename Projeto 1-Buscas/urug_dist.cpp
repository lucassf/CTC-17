#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
#define EPS 1e-9

/*Definição das estruturas de dados*/

class city{
public:
    double coord_x,coord_y;
    city(){}
    city(double _x,double _y,vector<int> &_adjList){
        coord_x = _x;
        coord_y = _y;
        adjList = _adjList;
    }
    vector<int> adjList;
};

struct state{
    double cost, dist;
    int u;

    state(double _cost,double _dist,int _u){
        u = _u, cost = _cost, dist = _dist;
    }
    state(){}

    bool operator <(state other) const{
        return cost>other.cost;
    }
};

struct result_set{
    int time_complexity, space_complexity;
    double total_dist;

    result_set(){}
    result_set(int _time_complexity, int _space_complexity, double _total_dist){
        time_complexity = _time_complexity, space_complexity = _space_complexity,
        total_dist = _total_dist;
    }
};

/*Retorna a distância entre duas cidades*/

double getDist(city c,city c1){
    double dy = c.coord_y - c1.coord_y;
    double dx = c.coord_x - c1.coord_x;
    return sqrt(dx*dx+dy*dy);
}

/*Algoritmo A*. A heuristica utilizada e valores retornados são os mesmos do greedy.*/

result_set a(int start,vector<city> &cities,int goal){
    int visited_states = 0, in_memory_states = 1;
    vector<double> g;
    priority_queue<state> inuse;

    g.assign(cities.size(),-1);
    inuse.push(state(0,0,start));
    g[start] = 0;

    int u,v;
    double f,dist,aux_dist;

    while (!inuse.empty()){
        in_memory_states = max(in_memory_states,(int)inuse.size());
        u = inuse.top().u;
        dist = inuse.top().dist;
        inuse.pop();

        if (dist>g[u])continue;
        visited_states++;
        if (u == goal)break;

        for (int i=0;i<(int)cities[u].adjList.size();i++){
            v = cities[u].adjList[i];
            aux_dist = getDist(cities[v],cities[u])+dist;
            f = getDist(cities[v],cities[goal])+aux_dist;

            if (g[v]==-1||aux_dist<g[v]){
                g[v] = aux_dist;
                inuse.push(state(f,aux_dist,v));
            }
        }
    }
    return result_set(visited_states, in_memory_states, g[goal]);
}

/*Algoritmo greedy. Como heurística definiu-se escolher o vértice mais próximo do objetivo.
Função retorna complexidade no tempo, complexidade no espaço e completude obtidos pelo
algoritmo.*/

result_set greedy(int start,vector<city> &cities,int goal){
    int visited_states = 0, in_memory_states = 1;
    vector<double> g;
    priority_queue<state> inuse;

    g.assign(cities.size(),-1);
    inuse.push(state(0,0,start));
    g[start] = 0;

    int u,v;
    double h,dist,aux_dist;

    while (!inuse.empty()){
        in_memory_states = max(in_memory_states,(int)inuse.size());
        u = inuse.top().u;
        dist = inuse.top().dist;
        inuse.pop();

        if (dist>g[u])continue;
        visited_states++;
        if (u == goal)break;

        for (int i=0;i<(int)cities[u].adjList.size();i++){
            v = cities[u].adjList[i];
            aux_dist = getDist(cities[v],cities[u])+dist;
            h = getDist(cities[v],cities[goal]);

            if (g[v]==-1||aux_dist<g[v]){
                g[v] = aux_dist;
                inuse.push(state(h,aux_dist,v));
            }
        }
    }
    return result_set(visited_states, in_memory_states, g[goal]);
}

/*Função que faz o parsing do arquivo de entrada.*/

bool parseFile(vector<city> &cities, ifstream& str){
    string line,cell;
    if (!getline(str,line))return false;
    int cnt = 0,id;
    double coord_x,coord_y;

    vector<int> adjList;

    while (getline(str,line)){
        stringstream lineStream(line);
        while (getline(lineStream,cell, ','))
        {
            if (cnt==0)id = atoi(cell.c_str());
            else if (cnt==1)coord_x = atof(cell.c_str());
            else if (cnt==2)coord_y = atof(cell.c_str());
            else{
                stringstream adjListStream(cell);
                while (getline(adjListStream,cell,' ')){
                    adjList.push_back(atoi(cell.c_str()));
                }
                cities.push_back(city(coord_x,coord_y,adjList));
                adjList.clear();
            }
            cnt = (cnt+1)%4;
        }
    }
    return true;
}

/*Função principal*/

int main(){
    vector<city> cities;
    ifstream infile;
    result_set greedy_results, a_results;

    cities.push_back(city());
    infile.open("Uruguay_correct.csv");
    if (!parseFile(cities,infile))return -1;

    greedy_results = greedy(203,cities,600);
    a_results = a(203,cities,600);

    cout<<"ALGORITMO GREEDY\n\n";
    cout<<"Complexidade no espaco: "<<greedy_results.space_complexity<<
        "\nComplexidade no tempo: "<<greedy_results.time_complexity<<
        "\nDistancia percorrida: "<<greedy_results.total_dist<<"\n";

    cout<<"\nALGORITMO A*\n\n";
    cout<<"Complexidade no espaco: "<<a_results.space_complexity<<
        "\nComplexidade no tempo: "<<a_results.time_complexity<<
        "\nDistancia percorrida: "<<a_results.total_dist<<"\n";

    return 0;
}
