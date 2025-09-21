#include <bits/stdc++.h>
using namespace std;

int n;

void solve() {
    cin >> n;
    long long ans = 0;
    function<void(int,int,int,int)> dfs = [&](int row, int col, int d1, int d2) {
        if (row == n) { ++ans; return; }
        int avail = ((1 << n) - 1) & ~(col | d1 | d2);
        while (avail) {
            int p = avail & -avail;          // 가장 오른쪽 1비트
            avail -= p;                      // 해당 자리 사용
            dfs(row + 1, col | p, (d1 | p) << 1, (d2 | p) >> 1);
        }
    };
    dfs(0, 0, 0, 0);
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
