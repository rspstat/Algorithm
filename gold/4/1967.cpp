#include <bits/stdc++.h>
using namespace std;

int n;

void solve() {
    cin >> n;
    vector<vector<pair<int,int>>> g(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b, w; 
        cin >> a >> b >> w;
        g[a].push_back({b, w});
        g[b].push_back({a, w});
    }

    auto bfs = [&](int start) {
        vector<int> dist(n + 1, -1);
        queue<int> q;
        dist[start] = 0;
        q.push(start);
        int far = start;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto [v, w] : g[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + w;
                    q.push(v);
                    if (dist[v] > dist[far]) far = v;
                }
            }
        }
        return pair<int, vector<int>>(far, dist);
    };

    if (n == 1) { cout << 0 << '\n'; return; }

    auto [u, _] = bfs(1);      // 임의의 노드에서 가장 먼 노드
    auto [v, dist] = bfs(u);   // u에서 가장 먼 노드까지의 거리 = 지름
    int diameter = *max_element(dist.begin(), dist.end());
    cout << diameter << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
