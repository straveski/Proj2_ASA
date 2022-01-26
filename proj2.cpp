#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

int buildGraph();
int checkGraphCycles();
int checkCycle(int node);
void DFS(int node, int flag);
int lowestAncestor();

//graph
int** graph;

//Vertices para descobrir os ancestrais
int v1, v2;

// N -> numero de vertices M -> numero de arcos
int N, M;

// vetor dos ancestrais de v1 e v2
vector<int> anc;
vector<int> res;


int main(){
    int g = buildGraph();
    if (g == -1){
        printf("0\n");
        return 0; 
    }
    DFS(v1,1);
    DFS(v2,2);

    int res = lowestAncestor();
    if(res == 0)
        printf("-");
    printf("\n");
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
            if(graph[pai][3] == 0){
                DFS(pai,1);
            }
        }
        else if(flag == 2){
            if(graph[pai][3] == 0 ||graph[pai][3] == 1){
                DFS(pai,2);
            }
        }
    }
    if(graph[node][3] == 2)
        anc.push_back(node);
}

int lowestAncestor(){
    int ancestor;
    int flag,flag2=0, pai;
    for(int i = 0; i < (int)anc.size(); i++){
        flag = 0;
        ancestor = anc[i];
        for(int j = 1; j < N+1; j++){
            for(int t = 0; t < graph[j][2]; t++){
                pai = graph[j][t];
                if(pai == ancestor){
                    if(graph[j][3] == 2)
                        flag++;
                }
            }
        }
        if(flag == 0){
            flag2++;
            res.push_back(ancestor);
        }
    }
    sort(res.begin(), res.end());
    /*for(int i = 0; i < (int)anc.size(); i++){
        printf("%d ", anc[i]);
    }
    printf("\n");*/
    for(int i = 0; i < (int)res.size(); i++){
        printf("%d ", res[i]);
    }

    return flag2;
}