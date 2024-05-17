#include <iostream>
#include <algorithm>
#include <vector>

#define INF 123456789
#define MAX 10001

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int dp[MAX];
    int arr[MAX];

    int n = 0, k = 0;
    cin >> n >> k;

    for (int i = 0; i < n; i++)
        cin >> arr[i];
    
    for (int i = 0; i <= k; i++)
        dp[i] = INF;  // 최솟값을 구하기 위해 최댓값 설정

    dp[0] = 0;  //초기 값 설정

    for (int i = 0; i < n; i++) {
        for (int j = arr[i]; j <= k; j++) 
            dp[j] = min(dp[j], dp[j - arr[i]] + 1);
    }

    if ( dp[k] == INF )
        cout << -1;

    else
        cout << dp[k];

    return 0;
}
