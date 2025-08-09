#include <bits/stdc++.h>

#define ll long long 

using namespace std;

bool isSquare(ll x) {
    if ( x < 0 ) {
        return false;
    }

    ll r = sqrt(x);

    return r * r == x;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;

    cin >> n >> m;

    vector<string> a(n);

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    ll ans = -1;

    for ( int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // 모든 등차 (dr, dc)
            for (int dr = -n; dr <= n; dr++) {
                for (int dc = -m; dc <= m; dc++) {
                    if (dr == 0 && dc == 0) continue;
                    
                    int r = i, c = j;

                    ll val = 0;

                    while (r >= 0 && r < n && c >= 0 && c < m) {
                        val = val * 10 + (a[r][c] - '0');

                        if (isSquare(val)) ans = max(ans, val);

                        r += dr;
                        c += dc;
                    }
                }
            }
            
        }
    }

    cout << ans << '\n';

    return 0;
}
