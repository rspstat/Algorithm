#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n = 0;
    cin >> n;

    vector<int> arr(n);
    vector<int> dp(n, 0);

    for (int i = 0; i < n; i++) 
        cin >> arr[i];
    
    //초기 값 설정
    dp[0] = arr[0];
    dp[1] = arr[0] + arr[1];
    dp[2] = max(arr[0] + arr[2], arr[1] + arr[2]);      //그 다음거 바로 할거냐 건너뛰고 더할거냐
    
    for (int i = 3; i < n; i++) 
        dp[i] += max(dp[i-3] + arr[i-1] + arr[i], dp[i-2] + arr[i]); //점화식
        
    //네번쨰 계단 = max(첫 계단 + 세번쨰 계단 + 네번째 계단 or 첫 + 두 번쨰 계단 + 네번째 계단)
    
    cout << dp[n - 1];

    return 0;
}

//3번 연속 밟지 마라
//도착점은 밟아라
//두 칸씩 오르기 가능
