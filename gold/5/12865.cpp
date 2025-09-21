#include <bits/stdc++.h>

using namespace std;

int n, w, v, k;

void solve() {
    cin >> n >> k;

    vector<int> dp(k+1, 0);

    for (int i = 0; i < n; ++i) {
        int wi, vi;
        cin >> wi >> vi;

        for (int j = k; j >= wi; --j) {
            dp[j] = max(dp[j], dp[j - wi] + vi);
        }
    }

    cout << *max_element(dp.begin(), dp.end()) << '\n';

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();

    return 0;
}
