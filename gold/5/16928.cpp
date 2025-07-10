#include <bits/stdc++.h>

using namespace std;

int n, m;   // 사다리의 수, 뱀의 수
int x, y;   // x = 사다리의 도착 칸, y = 칸 이동 수
int u, v;   // u = 뱀의 도착 칸, v = 칸 이동 수

int board[101];
bool visited[101];

int bfs() {
    queue<pair<int, int>> q;   // 현재 칸, 주사위 횟수
    q.push({1, 0});
    visited[1] = true;

    while (!q.empty()) {
        auto [cur, cnt] = q.front();
        q.pop();

        if (cur == 100)     // 도착!
            return cnt; 

        for (int d = 1; d <= 6; ++d) {
            int nxt = cur + d;

            if (nxt > 100)  
                continue;

            // 사다리 또는 뱀이 있으면 목적지로 순간이동
            if (board[nxt])
                nxt = board[nxt];

            if (!visited[nxt]) {    // 방문하지 않았으면
                visited[nxt] = true;    // 방문했다고 체크
                q.push({nxt, cnt + 1});     // 다음과 현재 + 1을 push -> 상태 업데이트
            }
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;

    for (int i = 0; i < n + m; ++i) {
        int a, b;
        cin >> a >> b;
        board[a] = b;
    }

    cout << bfs() << '\n';
 
    return 0;
}
