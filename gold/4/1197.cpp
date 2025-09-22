#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

vector<int> p;

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

bool unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return false;
    p[y] = x;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int v, e;
    cin >> v >> e;
    
    vector<Edge> edges(e);
    p.resize(v + 1);
    
    for (int i = 1; i <= v; i++) {
        p[i] = i;
    }
    
    for (int i = 0; i < e; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    
    sort(edges.begin(), edges.end());
    
    long long ans = 0;
    
    for (auto& edge : edges) {
        if (unite(edge.u, edge.v)) {
            ans += edge.w;
        }
    }
    
    cout << ans << "\n";
    
    return 0;
}
