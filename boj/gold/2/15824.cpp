#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1000000007;

ll mpow(ll a, ll e) {
    ll r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());

    vector<ll> p(n);
    p[0] = 1;
    for (int i = 1; i < n; i++) p[i] = (p[i-1] * 2) % MOD;

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ll add = (a[i] * (p[i] - p[n-1-i] + MOD)) % MOD;
        ans = (ans + add) % MOD;
    }
    cout << ans << "\n";
}
