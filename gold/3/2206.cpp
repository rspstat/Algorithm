#include <bits/stdc++.h>
using namespace std;

int n, m;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

struct Node {
    int x, y, w;
};

void solve() {
    cin >> n >> m;
    vector<string> grid(n);
    for (int i = 0; i < n; ++i) cin >> grid[i];

    vector<vector<vector<int>>> dist(n, vector<vector<int>>(m, vector<int>(2, -1)));
    queue<Node> q;

    dist[0][0][0] = 1;
    q.push({0, 0, 0});

    while (!q.empty()) {
        auto [x, y, w] = q.front();
        q.pop();
        if (x == n - 1 && y == m - 1) {
            cout << dist[x][y][w] << '\n';
            return;
        }
        for (int dir = 0; dir < 4; ++dir) {
            int nx = x + dx[dir], ny = y + dy[dir];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            // 벽이 아닌 경우
            if (grid[nx][ny] == '0' && dist[nx][ny][w] == -1) {
                dist[nx][ny][w] = dist[x][y][w] + 1;
                q.push({nx, ny, w});
            }
            // 벽인 경우 & 아직 안 부쉈다면
            if (grid[nx][ny] == '1' && w == 0 && dist[nx][ny][1] == -1) {
                dist[nx][ny][1] = dist[x][y][w] + 1;
                q.push({nx, ny, 1});
            }
        }
    }
    cout << -1 << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
