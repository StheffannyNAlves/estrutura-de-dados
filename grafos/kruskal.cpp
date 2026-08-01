#include <bits/stdc++.h>
using namespace std;

struct UnionFind {
    vector<int> pai, rank_;
    UnionFind(int n) {
        pai.resize(n + 1);
        rank_.assign(n + 1, 0);
        for (int i = 1; i <= n; i++) pai[i] = i;
    }
    int find(int x) {
        if (pai[x] != x) pai[x] = find(pai[x]);
        return pai[x];
    }
    void unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return;
        if (rank_[rx] < rank_[ry]) swap(rx, ry);
        pai[ry] = rx;
        if (rank_[rx] == rank_[ry]) rank_[rx]++;
    }
};

struct Aresta {
    int u, v, peso;
};

int main(){
    int V, E;
    cin >> V >> E;

    vector<Aresta> arestas(E);
    for (int i = 0; i < E; i++)
        cin >> arestas[i].u >> arestas[i].v >> arestas[i].peso;

    sort(arestas.begin(), arestas.end(), [](const Aresta& a, const Aresta& b) {
        return a.peso < b.peso;
    });

    UnionFind uf(V);
    int pesoTotal = 0;
    int arestasUsadas = 0;

    for (auto& a : arestas) {
        if (uf.find(a.u) != uf.find(a.v)) {
            uf.unite(a.u, a.v);
            pesoTotal += a.peso;
            arestasUsadas++;
            cout << a.u << " -- " << a.v << " (peso " << a.peso << ")\n";
        }
    }

    cout << "peso total da MST: " << pesoTotal << "\n";

    if (arestasUsadas < V - 1)
        cout << "aviso: grafo desconexo, MST nao cobre todos os vertices\n";

    return 0;
}