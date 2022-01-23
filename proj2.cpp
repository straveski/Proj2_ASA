#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int buildGraph();
int checkGraph();

//graph
int** graph;

//Vertices para descobrir os ancestrais
int v1, v2;

// N -> numero de vertices M -> numero de arcos
int N, M;

int main(){
    int g = buildGraph();
    if (g == -1){
        cout << "0" << endl;
        return 0; 
    }
    cout << "2" << endl;
    return 0;
}

int buildGraph(){
    cin >> v1 >> v2;
    cin >> N >> M;
    graph = (int**)malloc((N+1) * sizeof(int*));
    // cada vetor do grafo vai ter PAI1|PA2|N PAIS|COR
    for(int i = 1; i < N+1; i++){
        graph[i] = (int*)malloc(4 * sizeof(int));
        for(int j=0; j<4; j++){
            graph[i][j] = 0;
        }
    }
    int error;
   for(int i = 0; i < M; i++){
        int ftr, cld;
        cin >> ftr >> cld;
        int n_pais = graph[cld][2];
        //filho tem mais de 2 pais
        if (n_pais == 2)
            error = -1;
        //atualizo o novo pai
        graph[cld][n_pais] = ftr;
        //atualizo o numero de pais
        graph[cld][2]++;
    }
    if(error == -1)
        return -1;
    if (checkGraph() == -1){
        return -1;
    }
    else
        return 0;
}

int checkGraph(){

    return 0;
}