#include <bits/stdc++.h>
using namespace std;

int main(){
    int V, E;
    cin >> V >> E;

    vector<vector<pair<int,int>>> adj(V + 1); 

    for (int i = 0; i < E; i++){
        int u, v, peso;
        cin >> u >> v >> peso;
        adj[u].push_back({v, peso});
        adj[v].push_back({u, peso});
    }

    vector<bool> visitado(V + 1, false);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> fila; 

    int origem = 1;
    fila.push({0, origem});
    int pesoTotal = 0;
    int arestasUsadas = 0;

    while (!fila.empty()){
        auto [peso, v] = fila.top();
        fila.pop();

        if (visitado[v]) continue;
        visitado[v] = true;
        pesoTotal += peso;
        if (peso > 0) arestasUsadas++;

        for (auto& [u, pesoAresta] : adj[v]){
            if (!visitado[u])
                fila.push({pesoAresta, u});
        }
    }

    cout << "peso total da MST: " << pesoTotal << "\n";

    if (arestasUsadas < V - 1)
        cout << "aviso: grafo desconexo, MST nao cobre todos os vertices\n";

    return 0;
}