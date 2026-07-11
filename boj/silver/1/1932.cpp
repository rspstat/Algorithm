#include <bits/stdc++.h>
using namespace std;

int n;

void solve() {
    cin >> n;
    vector<vector<int>> a(n);
    for (int i = 0; i < n; ++i) {
        a[i].resize(i + 1);
        for (int j = 0; j <= i; ++j) cin >> a[i][j];
    }

    vector<int> dp = a.back(); // 마지막 행으로 초기화
    for (int i = n - 2; i >= 0; --i) {
        for (int j = 0; j <= i; ++j) {
            dp[j] = a[i][j] + max(dp[j], dp[j + 1]);
        }
    }
    cout << dp[0] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
