#include <bits/stdc++.h>
using namespace std;

int v;

void solve() {
    cin >> v;
    vector<vector<pair<int,int>>> g(v + 1);
    for (int i = 0; i < v; ++i) {
        int u; cin >> u;
        while (true) {
            int to; cin >> to;
            if (to == -1) break;
            int w; cin >> w;
            g[u].push_back({to, w});
        }
    }

    auto bfs = [&](int start) {
        vector<int> dist(v + 1, -1);
        queue<int> q;
        dist[start] = 0;
        q.push(start);
        int far_node = start;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto [to, w] : g[u]) {
                if (dist[to] == -1) {
                    dist[to] = dist[u] + w;
                    q.push(to);
                    if (dist[to] > dist[far_node]) far_node = to;
                }
            }
        }
        return pair<int, vector<int>>(far_node, dist);
    };

    // 1. 임의의 노드(1)에서 가장 먼 노드를 찾음
    auto [node1, _] = bfs(1);
    // 2. node1에서 가장 먼 노드를 찾고, 그 거리 = 트리의 지름
    auto [node2, dist] = bfs(node1);
    int diameter = *max_element(dist.begin(), dist.end());

    cout << diameter << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
