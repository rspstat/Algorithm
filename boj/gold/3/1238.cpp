#include <bits/stdc++.h>
using namespace std;

int n, m, x;

vector<int> dijkstra(int start, const vector<vector<pair<int,int>>>& g) {
    const int INF = 1e9;
    vector<int> dist(n + 1, INF);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    dist[start] = 0;
    pq.push({0, start});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : g[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

void solve() {
    cin >> n >> m >> x;
    vector<vector<pair<int,int>>> g(n + 1), rg(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b, t; cin >> a >> b >> t; // a -> b, cost t
        g[a].push_back({b, t});
        rg[b].push_back({a, t});         // 역방향 그래프
    }

    // X -> i (파티에서 집으로)
    vector<int> fromX = dijkstra(x, g);
    // i -> X (집에서 파티로) == X에서 역그래프로 최단거리
    vector<int> toX   = dijkstra(x, rg);

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans = max(ans, toX[i] + fromX[i]);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
