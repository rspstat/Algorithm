#include <bits/stdc++.h>
using namespace std;

int n, m;

void solve() {
    cin >> n >> m;
    vector<vector<int>> psum(n+1, vector<int>(n+1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int x; cin >> x;
            psum[i][j] = psum[i-1][j] + psum[i][j-1] - psum[i-1][j-1] + x;
        }
    }

    ostringstream out;
    while (m--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        int ans = psum[x2][y2] - psum[x1-1][y2] - psum[x2][y1-1] + psum[x1-1][y1-1];
        out << ans << '\n';
    }
    cout << out.str();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
