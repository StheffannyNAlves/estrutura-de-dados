#include <iostream>
#include <queue>
#include <vector>


using namespace std;


vector<vector<int>> create(int V, int E, vector<int>& inDegree){
   vector<vector<int>> graph(V);
   int v, u;

   for (int i = 0; i < E; i++){
     cin >> v >> u;
     graph[v].push_back(u);
     inDegree[u]++; 
   }

   return graph;
}

vector<int> kahn(vector<vector<int>>& graph, vector<int> inDegree, int V){
  queue<int> fila;
  vector<int> ordem;
 
  for (int v = 0; v < V; v++){
    if (inDegree[v] == 0)
      fila.push(v);
  }
 
  while (!fila.empty()){
    int v = fila.front();
    fila.pop();
    ordem.push_back(v);
 
    for (auto u : graph[v]){
      inDegree[u]--;
      if (inDegree[u] == 0)
        fila.push(u);
    }
  }
 
  return ordem;
}
 
int main(){
  int V, E;
  cin >> V >> E;
 
  vector<int> inDegree(V, 0);
  vector<vector<int>> graph = create(V, E, inDegree);
 
  vector<int> ordem = kahn(graph, inDegree, V);
 
  if ((int)ordem.size() < V){
    cout << "ciclo detectado, nao existe ordenacao topologica" << endl;
  } else {
    for (int v : ordem) cout << v << " ";
    cout << endl;
  }
}
 