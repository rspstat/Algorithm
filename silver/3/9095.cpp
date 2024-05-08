#include <iostream>
#include <vector>

using namespace std;

int dp[11];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int T = 0, tmp = 0;
    cin >> T;

    vector<int> dp(12, 0);

    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 4;

    for (int i = 4; i < 12; i++) 
        dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
    
    for (int i = 0; i < T; i++) {
        cin >> tmp;
        cout << dp[tmp] << endl;
    }


    return 0;
}

//a[n] = a[n-1] + a[n-2] + a[n-3];
