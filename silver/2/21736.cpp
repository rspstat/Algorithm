#include <iostream>
#include <queue>

using namespace std;

int n, m;
char campus[601][601];
bool visited[601][601];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int bfs(int startX, int startY) {
    queue<pair<int, int>> q;
    q.push({startX, startY});
    visited[startX][startY] = true;
    int friendCnt = 0;

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                if (!visited[nx][ny] && campus[nx][ny] != 'X' ) {
                    visited[nx][ny] = true;
                    q.push({nx, ny});
                    if (campus[nx][ny] == 'P') {
                        friendCnt++;
                    }
                }
            }
        }
    }

    return friendCnt;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    int startX, startY;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> campus[i][j];
            if (campus[i][j] == 'I') {
                startX = i;
                startY = j;
            }
        }
    }

    int res = bfs(startX, startY);

    if (res == 0) {
        cout << "TT\n";
    }

    else {
        cout << res << "\n";
    }

    return 0;
}
