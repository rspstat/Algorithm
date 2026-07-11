#include <iostream>
#include <algorithm>
#include <vector>

#define ll long long

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, k, res = -100001;    //범위의 최솟값으로 reset in res
    cin >> n >> k;

    vector<int> dp(n + 1);

    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        int num;
        cin >> num;              //구간 합 공식은 거의 다 이거1
        dp[i] = dp[i - 1] + num; //ex) 3 -2 -4 -9 13... -> 3 1 -3 -12 1... in dp
    }

    for (int i = k; i <= n; i++) {
        res = max(res, dp[i] - dp[i - k]);    //구간 합 공식은 거의 다 이거2
    }

    cout << res;
    
    return 0;
}
