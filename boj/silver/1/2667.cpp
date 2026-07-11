#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
vector<vector<int>> map;
vector<vector<bool>> visited;
vector<int> clusterSizes;

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

int dfs(int x, int y) {
    visited[x][y] = true;
    int count = 1;

    for (int dir = 0; dir < 4; dir++) {
        int nx = x + dx[dir];
        int ny = y + dy[dir];

        if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
            if (!visited[nx][ny] && map[nx][ny] == 1) {
                count += dfs(nx, ny);
            }
        }
    }
    return count;
}

int main() {
    cin >> N;
    map.resize(N, vector<int>(N));
    visited.resize(N, vector<bool>(N, false));

    // 입력 받기
    for (int i = 0; i < N; i++) {
        string row;
        cin >> row;
        for (int j = 0; j < N; j++) {
            map[i][j] = row[j] - '0';
        }
    }

    // DFS로 단지 탐색
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!visited[i][j] && map[i][j] == 1) {
                int size = dfs(i, j);
                clusterSizes.push_back(size);
            }
        }
    }

    // 결과 출력
    sort(clusterSizes.begin(), clusterSizes.end());
    cout << clusterSizes.size() << '\n';
    for (int size : clusterSizes) {
        cout << size << '\n';
    }

    return 0;
}