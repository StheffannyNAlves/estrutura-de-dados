#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

vector<vector<int>> create(int V, int E){
   vector<vector<int>> graph(V);
   int v, u;

   for (int i = 0; i < E; i++){
     cin >> v >> u;
     graph[v].push_back(u);
     graph[u].push_back(v); 
   }

   return graph;
}

void dfs(vector<vector<int>> graph, int v, vector<bool>& visitado){
    visitado[v] = true;

    for(int vizinho : graph[v]){
        if(!visitado[v]){
            dfs(graph, v, visitado);
        }
    }
}


int main(){
    int V, A, T, N;
    cin >> T;


    while(T--){
        cin >> N;
        cin >> V >> A;
        int v;

        vector<vector<int>> graph = create(V, A);
        vector<bool> visitado(V, false);

        dfs(graph, v, visitado);

        cout << endl;
    }



    return 0;

}