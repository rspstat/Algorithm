#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int MAX = 50;
int field[MAX][MAX];
bool visited[MAX][MAX];
int dx[4] = {0, 0, -1, 1};  // 상 하 좌 우 
int dy[4] = {-1, 1, 0, 0};  // 상 하 좌 우

void bfs(int x, int y, int M, int N) {
    queue<pair<int, int>> q;
    q.push({x, y});
    visited[x][y] = true;

    while (!q.empty()) {
        int curX = q.front().first;
        int curY = q.front().second;

        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = curX + dx[i];
            int ny = curY + dy[i];

            // 범위 체크 및 방문 체크, 배추가 있는 위치인지 확인
            if (nx >= 0 && nx < M && ny >= 0 && ny < N && !visited[nx][ny] && field[nx][ny] == 1) {
                    visited[nx][ny] = true;
                    q.push({nx, ny});
            } 
        }
    }

}

int main() {
    int t;
    cin >> t;

    while (t--) {
        int m, n, k; // 가로 길이, 세로 길이, 위치의 개수

        cin >> m >> n >> k;

        // 밭 초기화
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                field[i][j] = 0;
                visited[i][j] = false;
            }
        }

        // 배추 위치 입력
        for (int i = 0; i < k; i++){
            int x, y;
            cin >> x >> y;
            field[x][y] = 1;
        }

        int count = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (field[i][j] == 1 && !visited[i][j]) {
                    bfs(i, j, m, n);
                    count++;
                }
            }
        }

        cout << count << endl;
    }

    return 0;
}
