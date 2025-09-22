#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int c, n;
    cin >> c >> n;
    
    vector<int> cost(n), cust(n);
    for (int i = 0; i < n; i++) {
        cin >> cost[i] >> cust[i];
    }
    
    vector<int> dp(c + 101, 100001);
    dp[0] = 0;
    
    for (int i = 0; i <= c + 100; i++) {
        if (dp[i] == 100001) continue;
        for (int j = 0; j < n; j++) {
            int nxt = min(c + 100, i + cust[j]);
            dp[nxt] = min(dp[nxt], dp[i] + cost[j]);
        }
    }
    
    int ans = 100001;
    for (int i = c; i <= c + 100; i++) {
        ans = min(ans, dp[i]);
    }
    
    cout << ans << "\n";
    
    return 0;
}
