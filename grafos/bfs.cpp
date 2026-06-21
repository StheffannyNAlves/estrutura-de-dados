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
vector<int> bfs(vector<vector<int>> graph, int source, int dest){
  int V = graph.size();
  vector<bool> visited(V, false);
  vector<int> antecessor(V, -1);
  queue<int> q;

  q.push(source);
  visited[source] = true;

  while (!q.empty() && !visited[dest]){
    int v = q.front();
    q.pop();

    for (auto u: graph[v]){
      if (!visited[u]){
        visited[u] = true;
        q.push(u);
        antecessor[u] = v;
      }
    }
  }

  return antecessor;
}

int main(){
  int V, E, source, dest;
  cin >> V >> E;
  vector<vector<int>> graph = create(V, E);

  cin >> source >> dest;
  vector<int> antecessor = bfs(graph, source, dest);
  stack<int> path;
  path.push(dest);
  int aux = dest;
  while (antecessor[aux] != -1){
    path.push(antecessor[aux]);
    aux = antecessor[aux];
  }

  int count = 0;
  while (!path.empty()){
    cout << path.top() << " ";
    path.pop();
    count++;
  }
  cout << endl << count-1 << endl;
}
