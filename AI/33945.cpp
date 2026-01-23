#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;

const int MOD = 1000000007;

int addm(int a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}

int subm(int a, int b) {
    a -= b;
    if (a < 0) a += MOD;
    return a;
}

int mulm(ll a, ll b) {
    return (int)((a % MOD) * (b % MOD) % MOD);
}

int pw(ll a, ll e) {
    ll r = 1 % MOD;
    a %= MOD;

    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }

    return (int)r;
}

int comb_sm(ll n, int r, const vector<int> &invf) {
    if (n < 0 || n < r) return 0;

    ll p = 1;
    for (int i = 0; i < r; i++) {
        ll t = (n - i) % MOD;
        if (t < 0) t += MOD;
        p = p * t % MOD;
    }

    return mulm(p, invf[r]);
}

int cnt_sum_rng(const vector<pair<ll, ll>> &rg, ll n, const vector<int> &invf) {
    int k = (int)rg.size();

    if (k == 1) {
        return (rg[0].first <= n && n <= rg[0].second) ? 1 : 0;
    }

    ll as = 0;
    vector<ll> r(k);

    for (int i = 0; i < k; i++) {
        as += rg[i].first;
        r[i] = rg[i].second - rg[i].first;
    }

    ll t = n - as;
    int rr = k - 1;

    int res = 0;
    int lim = 1 << k;

    for (int msk = 0; msk < lim; msk++) {
        ll cut = 0;
        int bc = 0;

        for (int i = 0; i < k; i++) {
            if (msk & (1 << i)) {
                cut += (r[i] + 1);
                bc++;
            }
        }

        ll tt = t - cut;
        int v = 0;

        if (tt >= 0) {
            ll nn = tt + rr;
            v = comb_sm(nn, rr, invf);
        }

        if (bc & 1) res = subm(res, v);
        else res = addm(res, v);
    }

    return res;
}

void gen_cmp(int k, int sum, int idx, vector<int> &cur, vector<vector<int>> &out) {
    if (idx == k) {
        if (sum == 0) out.push_back(cur);
        return;
    }

    int rem = k - idx;
    for (int x = 1; x <= sum - (rem - 1); x++) {
        cur[idx] = x;
        gen_cmp(k, sum - x, idx + 1, cur, out);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ll n;
    int m;
    cin >> n >> m;

    vector<ll> p10(12, 1);
    for (int i = 1; i <= 11; i++) {
        p10[i] = p10[i - 1] * 10LL;
    }

    vector<int> f(6, 1);
    for (int i = 1; i <= 5; i++) {
        f[i] = mulm(f[i - 1], i);
    }

    vector<int> invf(6, 1);
    for (int i = 0; i <= 5; i++) {
        invf[i] = pw(f[i], MOD - 2);
    }

    int ans = 0;

    for (int k = 1; k <= 6; k++) {
        int d = m - (k - 1);
        if (d < k) continue;

        vector<vector<int>> cs;
        vector<int> cur(k);
        gen_cmp(k, d, 0, cur, cs);

        int lim = 1 << (k - 1);

        for (auto &ls : cs) {
            for (int msk = 0; msk < lim; msk++) {
                vector<pair<ll, ll>> rg(k);

                for (int i = 0; i < k; i++) {
                    ll l, u;

                    if (ls[i] == 1) {
                        l = 0;
                        u = 9;
                    } else {
                        l = p10[ls[i] - 1];
                        u = p10[ls[i]] - 1;
                    }

                    int sg = (i == 0) ? 1 : (((msk >> (i - 1)) & 1) ? -1 : 1);

                    if (sg == 1) rg[i] = { l, u };
                    else rg[i] = { -u, -l };
                }

                ans = addm(ans, cnt_sum_rng(rg, n, invf));
            }
        }
    }

    cout << ans << "\n";

    return 0;
}
