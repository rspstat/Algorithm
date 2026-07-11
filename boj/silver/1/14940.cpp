#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m;
vector<vector<int>> graph;
vector<vector<int>> dist;
vector<vector<bool>> visited;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void bfs(int sx, int sy) {
    queue<pair<int, int>> q;
    q.push({sx, sy});
    visited[sx][sy] = true;
    dist[sx][sy] = 0;

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                if (!visited[nx][ny] && graph[nx][ny] == 1) {
                    visited[nx][ny] = true;
                    dist[nx][ny] = dist[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;
    graph.assign(n, vector<int>(m));
    dist.assign(n, vector<int>(m, -1));
    visited.assign(n, vector<bool>(m, false));

    int start_x, start_y;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> graph[i][j];
            if (graph[i][j] == 2) {
                start_x = i;
                start_y = j;
            }
        }
    }

    bfs(start_x, start_y);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (graph[i][j] == 0) 
                cout << 0 << " ";
            else
                cout << dist[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
