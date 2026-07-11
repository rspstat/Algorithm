#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int n, cnt;
char grid[101][101];
string input;
bool visited[101][101];

int dx[] = { 1, -1, 0, 0 } ;// 상하좌우
int dy[] = { 0, 0, 1, -1 };

void dfs(int nowx, int nowy) {
    if (visited[nowx][nowy])
        return;

    visited[nowx][nowy] = true;

    for (int i = 0; i < 4; i++) {
        int X = dx[i] + nowx;
        int Y = dy[i] + nowy;

        // 다음 탐색하는 좌표가 현재 좌표와 색이 같고 방문하지 않았다면
        if ((grid[nowx][nowy] == grid[X][Y] && !visited[X][Y]))
            dfs(X, Y);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> input;
        for (int j = 0; j < n; j++) {
            grid[i][j] = input[j];  // 한 줄에서 한 글자씩 gird의 한 칸에 집어 넣음
        }
    }

    // 정상인 기준

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!visited[i][j]) {
                dfs(i, j);
                cnt++;  // 구역 수 1 증가
            }
        }
    }

    cout << cnt << " ";

    cnt = 0;

    memset(visited, false, sizeof(visited));

    // 적록색약 기준

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 'G') 
                grid[i][j] = 'R';
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!visited[i][j]) {
                dfs(i, j);
                cnt++;
            }
        }
    }

    cout << cnt;

    return 0;
}
