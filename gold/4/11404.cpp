#include <bits/stdc++.h>
using namespace std;

int n, m;

void solve() {
    cin >> n >> m;
    const int INF = 1e9;
    vector<vector<int>> dist(n+1, vector<int>(n+1, INF));

    for (int i = 1; i <= n; ++i) dist[i][i] = 0;

    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        dist[a][b] = min(dist[a][b], c); // 여러 간선 중 최소 비용만
    }

    // Floyd-Warshall
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    ostringstream out;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (dist[i][j] == INF) out << 0 << ' ';
            else out << dist[i][j] << ' ';
        }
        out << '\n';
    }
    cout << out.str();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
