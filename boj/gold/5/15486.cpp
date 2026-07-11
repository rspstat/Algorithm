#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N = 0;
    cin >> N;   //1 ~ 1,500,000, O(N)
    
    vector<int> dp(N + 1, 0);
    int res = 0, cur = 0;

    for (int i = 0; i < N; i++) {
        int day, cost;
        cin >> day >> cost;

        cur = max(cur, dp[i]);

        if ( i + day <= N ) {
            dp[i + day] = max(dp[i + day], cur + cost);
            res = max(dp[i + day], res);
        }
    }

    cout << res;
    
    return 0;
}

//day = T, cost = P
//dp[i + T] = max(dp[i + T], cur + P);
