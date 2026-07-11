#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MX = 500005;
const ll INF = 2e18;

int sz = 1;
ll tu[MX * 4], td[MX * 4];

void upd(ll* tr, int i, ll v) {
    i += sz;
    tr[i] = max(tr[i], v);
    for (i /= 2; i >= 1; i /= 2) {
        tr[i] = max(tr[i * 2], tr[i * 2 + 1]);
    }
}

ll qry(ll* tr, int l, int r) {
    ll ret = -INF;
    for (l += sz, r += sz; l <= r; l /= 2, r /= 2) {
        if (l % 2 == 1) ret = max(ret, tr[l++]);
        if (r % 2 == 0) ret = max(ret, tr[r--]);
    }
    return ret;
}

struct Mrk {
    int t, l, m;
    bool operator<(const Mrk& o) const {
        if (t != o.t) return t < o.t;
        return l < o.l;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, u, d, s;
    cin >> n >> u >> d >> s;
    
    vector<Mrk> mrk(n);
    for (int i = 0; i < n; i++) {
        cin >> mrk[i].t >> mrk[i].l >> mrk[i].m;
    }
    sort(mrk.begin(), mrk.end());
    
    while (sz <= MX) sz *= 2;
    
    for (int i = 0; i < sz * 2; i++) {
        tu[i] = td[i] = -INF;
    }
    
    upd(tu, s, (ll)s * u);
    upd(td, s, -(ll)s * d);
    
    for (int i = 0; i < n; ) {
        int j = i;
        while (j < n && mrk[j].t == mrk[i].t) j++;
        
        vector<pair<int,ll>> bt;
        for (int k = i; k < j; k++) {
            if (bt.empty() || bt.back().first != mrk[k].l) {
                bt.push_back({mrk[k].l, mrk[k].m});
            } else {
                bt.back().second += mrk[k].m;
            }
        }
        
        int m = bt.size();
        vector<ll> dp(m, -INF), base(m, -INF);
        
        for (int k = 0; k < m; k++) {
            int loc = bt[k].first;
            ll mon = bt[k].second;
            
            ll vl = qry(tu, 1, loc);
            if (vl != -INF) vl -= (ll)loc * u;
            
            ll vr = qry(td, loc, MX);
            if (vr != -INF) vr += (ll)loc * d;
            
            base[k] = max(vl, vr);
            if (base[k] != -INF) base[k] += mon;
        }
        
        ll cur = -INF;
        for (int k = 0; k < m; k++) {
            int loc = bt[k].first;
            ll mon = bt[k].second;
            
            if (cur != -INF) {
                cur -= (ll)(loc - bt[k-1].first) * u;
                cur += mon;
            }
            
            cur = max(cur, base[k]);
            dp[k] = cur;
        }
        
        cur = -INF;
        for (int k = m - 1; k >= 0; k--) {
            int loc = bt[k].first;
            ll mon = bt[k].second;
            
            if (cur != -INF) {
                cur -= (ll)(bt[k+1].first - loc) * d;
                cur += mon;
            }
            
            cur = max(cur, base[k]);
            dp[k] = max(dp[k], cur);
        }
        
        for (int k = 0; k < m; k++) {
            if (dp[k] != -INF) {
                int loc = bt[k].first;
                upd(tu, loc, dp[k] + (ll)loc * u);
                upd(td, loc, dp[k] - (ll)loc * d);
            }
        }
        
        i = j;
    }
    
    ll ans = 0;
    ll vl = qry(tu, 1, s);
    if (vl != -INF) ans = max(ans, vl - (ll)s * u);
    
    ll vr = qry(td, s, MX);
    if (vr != -INF) ans = max(ans, vr + (ll)s * d);
    
    cout << ans << '\n';
    
    return 0;
}
