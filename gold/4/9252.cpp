#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string a, b;
    cin >> a >> b;
    
    int n = a.length();
    int m = b.length();
    
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    
    cout << dp[n][m] << "\n";
    
    if (dp[n][m] > 0) {
        string lcs = "";
        int i = n, j = m;
        
        while (i > 0 && j > 0) {
            if (a[i - 1] == b[j - 1]) {
                lcs = a[i - 1] + lcs;
                i--;
                j--;
            } else if (dp[i - 1][j] > dp[i][j - 1]) {
                i--;
            } else {
                j--;
            }
        }
        
        cout << lcs << "\n";
    }
    
    return 0;
}
