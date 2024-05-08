#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n = 0;
    cin >> n;

    vector<int> dp(n + 1, 0);

    dp[1] = 1;  //2x1
    dp[2] = 2;  //2x2
    //dp[3] = 3; //2x3
    //dp[4] = 5; //2x4...
    //점화식 : dp[i] = dp[i-1] + dp[i-2];
 
    for (int i = 3; i <= n; i++) 
        dp[i] = (dp[i-1] + dp[i-2]) % 10007;
    
    cout << dp[n];

    return 0;
}
