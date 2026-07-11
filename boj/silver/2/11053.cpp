#include <bits/stdc++.h>

using namespace std;

#define MAX 1000

int a[MAX];
int dp[MAX];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> a[i];

        dp[i] = 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i])
                dp[i] = max(dp[i], dp[j] + 1);
        }
    }

    cout << *max_element(dp, dp + n);

    return 0;
}
