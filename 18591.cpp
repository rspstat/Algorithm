#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using i128 = __int128_t;

static ll gcdll(ll a, ll b) {
    while (b) {
        ll t = a % b;
        a = b;
        b = t;
    }
    return a;
}

static ll lcmll(ll a, ll b) {
    return a / gcdll(a, b) * b;
}

static ll count_res(ll l, ll r, ll mod, ll rem) {
    if (l > r) return 0;
    ll lm = l % mod;
    ll delta = (rem - lm) % mod;
    if (delta < 0) delta += mod;
    ll first = l + delta;
    if (first > r) return 0;
    return 1 + (r - first) / mod;
}

static inline int modnorm(ll x, int m) {
    ll v = x % m;
    if (v < 0) v += m;
    return (int)v;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        ll m;
        cin >> n >> m;

        vector<ll> xi(n), yi(n);
        vector<int> ki(n), ti(n);

        ll L = 1;
        for (int i = 0; i < n; i++) {
            cin >> xi[i] >> yi[i] >> ki[i] >> ti[i];
            L = lcmll(L, (ll)ki[i]);
        }

        vector<ll> cutX, cutY;
        cutX.reserve(n + 2);
        cutY.reserve(n + 2);
        cutX.push_back(0);
        cutX.push_back(m + 1);
        cutY.push_back(0);
        cutY.push_back(m + 1);
        for (int i = 0; i < n; i++) {
            cutX.push_back(xi[i]);
            cutY.push_back(yi[i]);
        }
        sort(cutX.begin(), cutX.end());
        cutX.erase(unique(cutX.begin(), cutX.end()), cutX.end());
        sort(cutY.begin(), cutY.end());
        cutY.erase(unique(cutY.begin(), cutY.end()), cutY.end());

        vector<pair<ll,ll>> xInts, yInts;
        for (int i = 0; i + 1 < (int)cutX.size(); i++) {
            ll l = cutX[i];
            ll r = cutX[i + 1] - 1;
            if (l <= r) xInts.push_back({l, r});
        }
        for (int i = 0; i + 1 < (int)cutY.size(); i++) {
            ll l = cutY[i];
            ll r = cutY[i + 1] - 1;
            if (l <= r) yInts.push_back({l, r});
        }

        vector<ll> cntX(L), cntY(L);
        i128 ans = 0;

        for (auto [xL, xR] : xInts) {
            for (ll rx = 0; rx < L; rx++) cntX[rx] = count_res(xL, xR, L, rx);

            for (auto [yL, yR] : yInts) {
                for (ll ry = 0; ry < L; ry++) cntY[ry] = count_res(yL, yR, L, ry);

                vector<int> sx(n), sy(n), ci(n);
                for (int i = 0; i < n; i++) {
                    sx[i] = (xL >= xi[i]) ? 1 : -1;
                    sy[i] = (yL >= yi[i]) ? 1 : -1;
                    ll c = -(ll)sx[i] * xi[i] - (ll)sy[i] * yi[i];
                    ci[i] = (int)c;
                }

                for (ll rx = 0; rx < L; rx++) {
                    if (cntX[rx] == 0) continue;
                    for (ll ry = 0; ry < L; ry++) {
                        if (cntY[ry] == 0) continue;

                        bool ok = true;
                        for (int i = 0; i < n; i++) {
                            int k = ki[i];
                            ll v = (ll)sx[i] * rx + (ll)sy[i] * ry + (ll)ci[i] - (ll)ti[i];
                            if (modnorm(v, k) != 0) { ok = false; break; }
                        }
                        if (ok) ans += (i128)cntX[rx] * (i128)cntY[ry];
                    }
                }
            }
        }

        long long out = (long long)ans;
        cout << out << "\n";
    }
    return 0;
}
