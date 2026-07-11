#include <iostream>
#include <vector>

#define ll long long
using namespace std;
const int MOD = 1000000000;

int main() {
    int N;
    cin >> N;

    // dp[pos][digit][mask]
    vector<vector<vector<ll>>> dp(N + 1, vector<vector<ll>>(10, vector<ll>(1024, 0)));

    // 초기 설정
    for (int i = 1; i <= 9; i++) 
        dp[1][i][1 << i] = 1;  // 길이가 1이고, 숫자 i로 시작하며, i만 사용한 상태

    for (int pos = 1; pos < N; pos++) {
        for (int digit = 0; digit <= 9; digit++) {
            for (int mask = 0; mask < 1024; mask++) {
                if (dp[pos][digit][mask] == 0) 
                    continue;

                // 다음 자릿수로 계단 수 확장
                if (digit + 1 <= 9) {
                    int next_mask = mask | (1 << (digit + 1));
                    dp[pos + 1][digit + 1][next_mask] = (dp[pos + 1][digit + 1][next_mask] + dp[pos][digit][mask]) % MOD;
                }
                if (digit - 1 >= 0) {
                    int next_mask = mask | (1 << (digit - 1));
                    dp[pos + 1][digit - 1][next_mask] = (dp[pos + 1][digit - 1][next_mask] + dp[pos][digit][mask]) % MOD;
                }
            }
        }
    }

    // 길이가 N이고, 모든 숫자를 포함한 계단 수의 개수 계산
    ll res = 0;
    for (int digit = 0; digit <= 9; digit++) 
        res = (res + dp[N][digit][1023]) % MOD;
    
    cout << res << endl;
    return 0;
}
