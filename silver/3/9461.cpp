// boj 9461번 파도반수열
#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t = 0;
    cin >> t;

    // 어이가 없네 이거, 규칙이 p(n) = p(n-2) + p(n-3) (n >= 4) 임...
    // dp 이거 그냥 규칙 찾기냐 ㅋㅋ;;

    long long dp[101] = {0, };

    dp[1] = dp[2] = dp[3] = 1;

    for (int i = 4; i <= 100; ++i) {
        dp[i] = dp[i-2] + dp[i-3];
    }

    while (t--) {
        int n = 0;
        cin >> n;

        cout << dp[n] << "\n";
    }

    return 0;
}
