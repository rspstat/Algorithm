#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;

struct Rc {
    ll xl;
    ll xr;
    ll yl;
    ll yr;
};

ll gap1(ll al, ll ar, ll bl, ll br) {
    if (ar < bl) return bl - ar;
    if (br < al) return al - br;
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<ll> x(n + 1), y(n + 1), p(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i] >> p[i];
    }

    Rc cur;
    cur.xl = x[1] - p[1];
    cur.xr = x[1] + p[1];
    cur.yl = y[1] - p[1];
    cur.yr = y[1] + p[1];

    ll ans = 0;

    for (int i = 2; i <= n; i++) {
        Rc nxt;
        nxt.xl = x[i] - p[i];
        nxt.xr = x[i] + p[i];
        nxt.yl = y[i] - p[i];
        nxt.yr = y[i] + p[i];

        ll dx = gap1(cur.xl, cur.xr, nxt.xl, nxt.xr);
        ll dy = gap1(cur.yl, cur.yr, nxt.yl, nxt.yr);
        ll d = max(dx, dy);

        ans += d;

        cur.xl -= d;
        cur.xr += d;
        cur.yl -= d;
        cur.yr += d;

        cur.xl = max(cur.xl, nxt.xl);
        cur.xr = min(cur.xr, nxt.xr);
        cur.yl = max(cur.yl, nxt.yl);
        cur.yr = min(cur.yr, nxt.yr);
    }

    cout << ans << "\n";

    return 0;
}
