#include <bits/stdc++.h>
using namespace std;

void solve() {
    int T; 
    cin >> T;
    ostringstream out;

    while (T--) {
        int n, m, w;
        cin >> n >> m >> w;

        struct Edge { int u, v, w; };
        vector<Edge> edges;
        edges.reserve(2*m + w);

        // 양방향 도로
        for (int i = 0; i < m; ++i) {
            int s, e, t; 
            cin >> s >> e >> t;
            edges.push_back({s, e, t});
            edges.push_back({e, s, t});
        }
        // 웜홀 (단방향, 음수 가중치)
        for (int i = 0; i < w; ++i) {
            int s, e, t; 
            cin >> s >> e >> t;
            edges.push_back({s, e, -t});
        }

        // Bellman-Ford: 모든 dist를 0으로 시작 -> 연결성 고려 없이 음수 사이클 탐지 가능
        vector<int> dist(n + 1, 0);
        bool updated = false;

        for (int i = 1; i <= n; ++i) {
            updated = false;
            for (const auto& ed : edges) {
                if (dist[ed.v] > dist[ed.u] + ed.w) {
                    dist[ed.v] = dist[ed.u] + ed.w;
                    updated = true;
                    if (i == n) break; // n번째에도 갱신되면 음수 사이클 존재
                }
            }
            if (!updated) break;
        }

        out << (updated ? "YES\n" : "NO\n");
    }

    cout << out.str();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
