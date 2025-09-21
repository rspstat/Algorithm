#include <bits/stdc++.h>
using namespace std;

int v, e, s;

void solve() {
    cin >> v >> e >> s;
    vector<vector<pair<int,int>>> g(v + 1);
    for (int i = 0; i < e; ++i) {
        int a, b, w; 
        cin >> a >> b >> w;      // 방향 그래프
        g[a].push_back({b, w});
    }

    const int INF = 1e9;
    vector<int> dist(v + 1, INF);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    dist[s] = 0;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [to, w] : g[u]) {
            if (dist[to] > dist[u] + w) {
                dist[to] = dist[u] + w;
                pq.push({dist[to], to});
            }
        }
    }

    ostringstream out;
    for (int i = 1; i <= v; ++i) {
        if (dist[i] == INF) out << "INF\n";
        else out << dist[i] << '\n';
    }
    cout << out.str();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
