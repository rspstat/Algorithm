#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n = 0;
    cin >> n;

    long long dp[50001] = {0, };

    dp[1] = 1;

    // 점화식을 알기 전에 미리 예시부터...
    // dp[101]을 구하려면? -> dp[1] + dp[100], dp[4] + dp[97], ... 이런식으로
    // dp[i] = dp[j * j] + dp[i - j * j]의 값들 중에서 최솟값을 구하면 됨
    // 여기서 제곱수(1, 4, 9, 16 ... )는 어차피 dp[j * j] == 1 이므로,
    // dp[i] = 1 + dp[i - j * j]가 된다. 근데 여기서, 자기 자신이 될 수도 있으므로,
    // dp[i] = dp[i]가 되는 경우도 생각해서 min을 씌워 최솟값을 구한다.
    
    for (int i = 2; i <= n; ++i) {
        dp[i] = i;  // worst case: 1^2을 i번 더한 경우... ex) 7에서 4 + 1 + 1 + 1이 되듯이.
        
        // 혹시 모르니까 dp[i]에 worst case를 먼저 넣은거임. 그리고 최솟값을 비교하면 되니까.
        for (int j = 1; j * j <= i; ++j) {
            // worst case보다 나은 case가 있다면 그걸 선택 (최솟값 인 것)
            // 만약 dp[101]을 구하려면 101을 1로 쭉 더한 개수를 선택할 것인가, 점화식대로 구할 것인가.
            dp[i] = min(dp[i], 1 + dp[i - j * j]);
        }
    }

    cout << dp[n];

    return 0;
}
