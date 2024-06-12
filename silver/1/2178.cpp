#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M;
int visited[100][100];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int bfs(int x, int y) {
    queue<pair<int, int>> q;

    q.push({x, y});

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;

        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if ( nx < 0 || nx >= N || ny < 0 || ny >= M ) 
                continue;

            if (visited[nx][ny] == 0)
                continue;

            if (visited[nx][ny] == 1) {
                visited[nx][ny] = visited[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    return visited[N - 1][M - 1];
}

int main() {
    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) 
            scanf("%1d", &visited[i][j]);
    }

    cout << bfs(0, 0) << endl;

    return 0;    
}
