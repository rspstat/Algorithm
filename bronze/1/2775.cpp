#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int dp[15][15];

    for (int i = 1; i < 15; i++) 
        dp[0][i] = i;       //0층 1 ~ 14호 까지 수를 넣음 -> 1, 2, 3, ... ,14

    for (int i = 1; i < 15; i++) {
        dp[i][1] = 1;
        for (int j = 2; j < 15; j++) 
            dp[i][j] = dp[i][j-1] + dp[i-1][j];
    }

    int t = 0;
    cin >> t;

    while (t--) {
        int k, n = 0;
        cin >> k >> n;
        cout << dp[k][n] << "\n";
    }

    return 0;
}

//001호 -> 1 002호 -> 1 + 1 003호 1 + 1 + 1
//101호 -> 1 102호 -> 1 + 1 + 1 103호 -> 1 + 1 + 1 + 1 + 1 + 1
//dp 기초
//만약 202호를 구하고 싶다면 102호 + 201호
//(1 + 1 + 1) + 1 = 4

