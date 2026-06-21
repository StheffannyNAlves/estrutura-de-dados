#include <iostream>
#include <queue>
#include <vector>
#include <list>
#include <utility>
#include <limits>

using namespace std;

vector<int> dijkstra(vector<list<pair<int, int> > > graph, int src, int dest){
    const int infinity = numeric_limits<int>::max();
    int V = graph.size();
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    vector<int> antecessors(V, -1);
    vector<int> weight(V, infinity);

    weight[src] = 0;
    pq.push(make_pair(0,src));

    while (!pq.empty()){
        int v = pq.top().second;
        if (v == dest)
            return antecessors;
        pq.pop();

        for (const auto& pair: graph[v]){
            int u = pair.first;
            int w = pair.second;
            if (weight[u] > weight[v] + w){
                weight[u] = weight[v] + w;
                pq.push(make_pair(weight[u],u));
                antecessors[u] = v;
            }
        }
    }

    return antecessors;
}

void init(vector<list<pair<int,int> > >& graph, int& V, int& E){
    int v, u, w;

    cin >> V >> E;
    graph.resize(V);
    for (int i = 0; i < E; i++){
        cin >> v >> u >> w;
        graph[v].push_back(make_pair(u,w));
        graph[u].push_back(make_pair(v,w)); // se grafo for não direcionado
    }
}

int main(){
    int V, E, src, dest;
    vector<list<pair<int,int> > > graph;
    init(graph, V, E);
    cin >> src >> dest;
    vector<int> antecessors = dijkstra(graph, src, dest);

    int aux = dest;
    while (antecessors[aux] != -1){
        cout << aux << " ";
        aux = antecessors[aux];
    }
    cout << aux << endl;
}
