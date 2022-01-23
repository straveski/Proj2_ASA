#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//Vertices para descobrir os ancestrais
vertex v1, v2;

// N -> numero de vertices M -> numero de arcos
int N = 0, M = 0;

//graph
vector<vertex> graph;

//estrutura de um vértice
typedef struct Vertex{
    //pais de um vertice
    vector<vertex> fathers;
    //lista de filhos do vertice
    vector<vertex> childrens;
    int id;
} *vertex;



int main(){
    buildGraph();
    return 0;
}

int buildGraph(){
    cin >> v1->id >> v2->id;
    cin >> N >> M;
    //inicializar o grafo com todos os vertices a NULL
    for(int i = 0; i < N; i++){
        graph[i] = NULL;
    }
    for(int i = 0; i < M; i++){
        vertex u,v;
        cin >> u->id >> v->id;
        (u->childrens).push_back(v);
        if ((v->fathers).size() == 2)
            return -1;
        (v->fathers).push_back(u);

    }


}