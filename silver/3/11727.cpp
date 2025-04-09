#include <iostream>

using namespace std;

#define ll long long
#define MAX 1001

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n = 0;

    ll dp[MAX] = {0, };

    cin >> n;

    dp[1] = 1;
    dp[2] = 3;
    
    // 점화식: dp[n] = dp[n-1] + 2 * dp[n-2]
    // 왜냐, 2x3을 생각했을 때, 경우의 수가 세로로 한개를 놓고(dp[n-1]), 2x1을 가로로 2개를 놓을 건지,
    // 2x2 타일을 하나 놓을 건지인데 결국 이건 dp[n-2]가 2가지 발생하므로 2*dp[n-2]가 되는거임.

    for (int i = 3; i <= 1000; ++i) {
        dp[i] = (dp[i - 1] + 2 * dp[i - 2]) % 10007;
    }

    cout << dp[n];

    return 0;
}
