#include <bits/stdc++.h>
using namespace std;

struct Pos  { int r, c; };
struct Node { Pos R, B; int d; };

int N, M;
char brd[11][11];

int dr[4] = { -1, 1, 0, 0 };
int dc[4] = {  0, 0,-1, 1 };

Pos roll(Pos p, int dir, Pos blk, bool &inHole) {
    int r = p.r, c = p.c;
    while (true) {
        int nr = r + dr[dir], nc = c + dc[dir];
        // 벽 또는 다른 구슬(blk) 앞에서 멈춤
        if (brd[nr][nc] == '#' || (nr == blk.r && nc == blk.c)) break;
        r = nr; c = nc;
        if (brd[r][c] == 'O') { inHole = true; break; }
    }
    return { r, c };
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;

    Pos R{0,0}, B{0,0};
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> brd[i][j];
            if (brd[i][j] == 'R') { R = { i, j }; brd[i][j] = '.'; }
            if (brd[i][j] == 'B') { B = { i, j }; brd[i][j] = '.'; }
        }
    }

    // 방문 체크 (rR,cR,rB,cB)
    static bool vis[11][11][11][11] = { false };
    queue<Node> q;

    vis[R.r][R.c][B.r][B.c] = true;
    q.push({ R, B, 0 });

    while (!q.empty()) {
        auto [r0, b0, d] = q.front(); q.pop();
        if (d >= 10) break;

        for (int dir = 0; dir < 4; ++dir) {
            bool hr = false, hb = false;
            Pos r1, b1;

            // 먼저 움직일 구슬 결정 (방향 기준 선두 먼저)
            bool redFirst =
                (dir == 0 && r0.r < b0.r) ||   // 위
                (dir == 1 && r0.r > b0.r) ||   // 아래
                (dir == 2 && r0.c < b0.c) ||   // 왼
                (dir == 3 && r0.c > b0.c);     // 오

            if (redFirst) {
                r1 = roll(r0, dir, b0, hr);
                // 빨강이 구멍으로 빠졌다면, 파랑은 '막힘 없이' 진행해야 함
                Pos blk = hr ? Pos{ -1, -1 } : r1;
                b1 = roll(b0, dir, blk, hb);
            } else {
                b1 = roll(b0, dir, r0, hb);
                Pos blk = hb ? Pos{ -1, -1 } : b1;
                r1 = roll(r0, dir, blk, hr);
            }

            if (hb) continue;          // 파랑 빠지면 실패 (해당 분기는 버림)
            if (hr) {                  // 빨강만 빠졌으면 성공
                cout << d + 1 << '\n';
                return 0;
            }

            if (!vis[r1.r][r1.c][b1.r][b1.c]) {
                vis[r1.r][r1.c][b1.r][b1.c] = true;
                q.push({ r1, b1, d + 1 });
            }
        }
    }

    cout << -1 << '\n';
    return 0;
}
