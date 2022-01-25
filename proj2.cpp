#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int buildGraph();
int checkGraphCycles();
int checkCycle(int node);
void DFS(int node, int flag);

//graph
int** graph;

//Vertices para descobrir os ancestrais
int v1, v2;

// N -> numero de vertices M -> numero de arcos
int N, M;

int main(){
    int g = buildGraph();
    if (g == -1){
        printf("0\n");
        return 0; 
    }
    DFS(v1,1);
    DFS(v2,2);
    int anc = 0;
    for(int i = 1; i < N+1; i++){
        if(graph[i][3] == 2)
            anc = i;
    }

    /*for(int i = 1; i < N+1; i++){
        for(int j = 0; j < 4; j++){
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }*/

    printf("%d \n",anc);
    return 0;
}

int buildGraph(){
    if(scanf("%d%d", &v1, &v2)){};
    if(scanf("%d%d", &N, &M)){};
    graph = (int**)malloc((N+1) * sizeof(int*));
    //indice 0 do vetor serve para armazenar valores de visitas na DFS
    graph[0] = (int*)malloc((N+1) * sizeof(int));
    for(int i = 0; i < N+1; i++)
        graph[0][i] = 0;
    // cada vetor do grafo vai ter PAI1|PAI2|N PAIS|NVISITED
    for(int i = 1; i < N+1; i++){
        graph[i] = (int*)malloc(4 * sizeof(int));
        for(int j=0; j<4; j++){
            graph[i][j] = 0;
        }
    }
    int error = 0;
    for(int i = 0; i < M; i++){
        int ftr, cld;
        if(scanf("%d%d", &ftr, &cld)){};
        int n_pais = graph[cld][2];
        //filho tem mais de 2 pais
        if(n_pais == 2){
            error = -1;
        }
        //atualizo o novo pai
        graph[cld][n_pais] = ftr;
        //atualizo o numero de pais
        graph[cld][2]++;
        }

    if(error == -1)
        return -1;

    if (checkGraphCycles() == -1)
        return -1;
    
    return 0;
}

//Use a DFS to check if a graph have cycles
int checkGraphCycles(){
    // vai percorrer os vertices 
    for(int i=1; i < N+1; i++ ){
        //verificar se n foi visitado vai visitar
        if(graph[i][3] == 0){
            if(checkCycle(i) == -1){
                return -1;
            }
        }
    }
    //volta a meter as entradas das visitas de DFS e dos vertices a 0
    for(int i=1; i < N+1; i++){
        graph[0][i] = 0;
        graph[i][3] = 0;
    }
    return 0;
}

int checkCycle(int node){
    graph[node][3] = 1;
    graph[0][node] = 1;
    // percorrer no max os 2 pais do vertice
    for(int i = 0; i < 2; i++){
        int pai = graph[node][i];
        // se n pai tiver para
        if(pai == 0){
            break;
        }
        //se o pai ja tiver sido visitado vamos ver os outros recursivamente
        else if(graph[pai][3] == 0){
            if(checkCycle(pai) == -1)
                return -1;
        }
        else if(graph[0][pai] == 1)
            return -1;
    }
    graph[0][node] = 0;
    return 0;
}

void DFS(int node, int flag){
    graph[node][3]++;
    for(int i = 0; i < 2; i++){
        int pai = graph[node][i];
        // se n pai tiver para
        if(pai == 0){
            break;
        }
        else if(flag == 1){
            if(graph[pai][3] == 0)
                DFS(pai,1);
        }
        else if(flag == 2){
            if(graph[pai][3] == 0 ||graph[pai][3] == 1)
                DFS(pai,2);
        }
    }
}