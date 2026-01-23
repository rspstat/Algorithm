#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using i128 = __int128_t;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> w(n + 1), sw(n + 1), lf(n + 1);
    for (int i = 1; i <= n; i++) cin >> w[i];

    for (int i = n; i >= 1; i--) {
        int l = i * 2, r = i * 2 + 1;
        if (l > n) {
            lf[i] = 1;
            sw[i] = w[i];
        } else {
            lf[i] = lf[l] + lf[r];
            sw[i] = w[i] + sw[l] + sw[r];
        }
    }

    auto ok = [&](int idx, ll t, const vector<int>& s) -> bool {
        i128 sum = (i128)lf[idx] * (i128)t;
        for (int a : s) {
            i128 prod = (i128)lf[a] * (i128)t;
            i128 ex = prod - (i128)sw[a];
            if (ex > 0) sum += ex;
        }
        return sum >= (i128)sw[idx];
    };

    vector<ll> ans(n + 1);

    for (int i = 1; i <= n; i++) {
        vector<int> s;
        for (int j = i; j > 1; j >>= 1) {
            int sib = (j & 1) ? (j - 1) : (j + 1);
            s.push_back(sib);
        }

        ll lo = 0, hi = 1;
        while (!ok(i, hi, s)) {
            if (hi > (LLONG_MAX / 2)) { hi = LLONG_MAX; break; }
            hi <<= 1;
        }

        while (lo < hi) {
            ll mid = lo + ((hi - lo) >> 1);
            if (ok(i, mid, s)) hi = mid;
            else lo = mid + 1;
        }
        ans[i] = lo;
    }

    for (int i = 1; i <= n; i++) {
        if (i > 1) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}
