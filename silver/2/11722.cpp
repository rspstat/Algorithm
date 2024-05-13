#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    vector<int> dp(1001, 0);
    vector<int> arr(1001, 0);

    int n = 0, res = 0;
    cin >> n;

    for (int i = 0; i < n; i++) 
        cin >> arr[i];

    for (int i = 0; i < n; i++) {
        dp[i] = 1;          //수열의 최소 크기 1

        for (int j = 0; j < i; j++) {   // i번쨰 값에서 왼쪽 값들중 더 큰 걸 찾는게 감소하는 수열 추출 가능 
            if (arr[i] < arr[j])   // <<< 값들중 더 큰걸 찾으면 
                dp[i] = max(dp[i], dp[j] + 1);  // dp[i] 변경 bcs 감소하는 수열의 크기를 +1
        }

        res = max(res, dp[i]);  //수열 길이중 가장 큰 값을 넣음
    }

    cout << res;
    
    return 0;
}
