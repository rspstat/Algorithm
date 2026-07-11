#include <iostream>
#include <algorithm>
#include <vector>

#define ll long long

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n = 0, m = 0; //수의 개수, 케이스 케수
    cin >> n >> m;

    vector<int> dp(n, 0);  

    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        int num;
        cin >> num;
        dp[i] = dp[i - 1] + num;    //ex) 5 4 3 2 1 -> 5 9 12 14 15 in dp
    }

    while (m--) {
        int left, right;
        cin >> left >> right;
        cout << dp[right] - dp[left - 1] << "\n";
    }
    
    return 0;
}
