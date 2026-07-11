#include <iostream>
#include <queue>
using namespace std;

const int MAX = 1000;
int box[MAX][MAX];        // 토마토 상태를 저장할 배열
int days[MAX][MAX];       // 익는 데 걸린 일수를 저장할 배열
int dx[4] = {1, -1, 0, 0}; // 상하좌우 이동을 위한 x방향 배열
int dy[4] = {0, 0, 1, -1}; // 상하좌우 이동을 위한 y방향 배열

int main() {
    int m, n; // m: 가로, n: 세로
    cin >> m >> n;

    queue<pair<int, int>> q;

    // 입력 받기
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < m; x++) {
            cin >> box[y][x];
            if (box[y][x] == 1) {
                q.push({y, x});       // 익은 토마토는 BFS 시작 지점
                days[y][x] = 0;       // 시작은 0일
            }
        }
    }

    // BFS 시작
    while (!q.empty()) {
        int cur_y = q.front().first;
        int cur_x = q.front().second;
        q.pop();

        // 4방향으로 탐색
        for (int i = 0; i < 4; i++) {
            int ny = cur_y + dy[i];
            int nx = cur_x + dx[i];

            // 범위 체크
            if (ny >= 0 && ny < n && nx >= 0 && nx < m) {
                // 안 익은 토마토일 경우만 전파
                if (box[ny][nx] == 0) {
                    box[ny][nx] = 1;                         // 익은 상태로 변경
                    days[ny][nx] = days[cur_y][cur_x] + 1;  // 현재 일수 +1
                    q.push({ny, nx});                       // 다음 탐색 대상으로 큐에 추가
                }
            }
        }
    }

    // 결과 확인
    int max_day = 0;
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < m; x++) {
            if (box[y][x] == 0) {
                cout << -1; // 아직 안 익은 토마토가 있으면 실패
                return 0;
            }
            max_day = max(max_day, days[y][x]); // 가장 오래 걸린 날짜 저장
        }
    }

    cout << max_day;
    return 0;
}
