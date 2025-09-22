#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) return 0;

    int n = (int)s.size();
    s = " " + s;                           // 1-index

    // pal[i][j] : s[i..j]가 팰린드롬인가?
    vector<vector<char>> pal(n + 1, vector<char>(n + 1, false));

    for (int i = 1; i <= n; ++i) pal[i][i] = true;                // 길이 1
    for (int i = 1; i + 1 <= n; ++i)                              // 길이 2
        pal[i][i + 1] = (s[i] == s[i + 1]);

    for (int len = 3; len <= n; ++len) {                          // 길이 3+
        for (int i = 1; i + len - 1 <= n; ++i) {
            int j = i + len - 1;
            pal[i][j] = (s[i] == s[j]) && pal[i + 1][j - 1];
        }
    }

    // dp[i] : s[1..i]를 팰린드롬들로 분할할 때 최소 개수
    const int INF = 1e9;
    vector<int> dp(n + 1, INF);
    dp[0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            if (pal[j][i]) dp[i] = min(dp[i], dp[j - 1] + 1);
        }
    }

    cout << dp[n] << '\n';
    return 0;
}
