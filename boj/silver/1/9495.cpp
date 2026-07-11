#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int T = 0;
    cin >> T;

    while (T--) {
        int arr[2][100001]; //두 배열 초기화 후 다시
        int dp[2][100001];

        int n = 0;
        cin >> n;

        for (int i = 0; i < n; i++) //스티커 2차원 배열 입력 받음
            cin >> arr[0][i];
        
        for (int i = 0; i < n; i++) 
            cin >> arr[1][i];

        dp[0][0] = arr[0][0];
        dp[1][0] = arr[1][0];
        dp[0][1] = arr[1][0] + arr[0][1];   // ↗ ↘ ...
        dp[1][1] = arr[0][0] + arr[1][1];   // ↘ ↗ ...

        for (int i = 2; i < n; i++) {
            dp[0][i] = max(dp[1][i-1], dp[1][i-2]) + arr[0][i];
            dp[1][i] = max(dp[0][i-1], dp[0][i-2]) + arr[1][i];
        }

        cout << max(dp[0][n-1], dp[1][n-1]) << "\n";
    }

    return 0;
}
