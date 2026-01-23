#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Md {
    int sz;
    int mn;
};

int cls(int v, int lo, int hi, int pr) {
    if (v < lo) v = lo;
    if (v > hi) v = hi;

    if ((v & 1) != pr) {
        if (v + 1 <= hi) v++;
        else v--;
    }

    return v;
}

int mindf(int alo, int ahi, int ap, int blo, int bhi, int bp) {
    int res = 2000000000;

    auto upd = [&](int y, int lo, int hi, int pr, int xlo, int xhi, int xp) {
        if (y < lo || y > hi) return;
        if ((y & 1) != pr) return;
        int x = cls(y, xlo, xhi, xp);
        res = min(res, abs(x - y));
    };

    vector<int> bc = { blo, blo + 2, bhi, bhi - 2 };
    vector<int> ac = { alo, alo + 2, ahi, ahi - 2 };

    for (int y : bc) upd(y, blo, bhi, bp, alo, ahi, ap);
    for (int x : ac) upd(x, alo, ahi, ap, blo, bhi, bp);

    return res;
}

Md joi(const Md &a, const Md &b) {
    if (a.sz == 0) return b;
    if (b.sz == 0) return a;

    int alo = a.mn, ahi = a.sz, ap = a.sz & 1;
    int blo = b.mn, bhi = b.sz, bp = b.sz & 1;

    int d = mindf(alo, ahi, ap, blo, bhi, bp);

    Md r;
    r.sz = a.sz + b.sz;
    r.mn = d;

    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int z;
    cin >> z;

    while (z--) {
        int n;
        cin >> n;

        vector<int> head(n + 1, -1);
        vector<int> to;
        vector<int> nx;
        to.reserve(n - 1);
        nx.reserve(n - 1);

        vector<int> rt;
        rt.reserve(n);

        for (int i = 1; i <= n; i++) {
            int p;
            cin >> p;

            if (p == -1) {
                rt.push_back(i);
            } else {
                int id = (int)to.size();
                to.push_back(i);
                nx.push_back(head[p]);
                head[p] = id;
            }
        }

        vector<int> ord;
        ord.reserve(n);

        vector<int> st;
        st.reserve(n);

        for (int r : rt) st.push_back(r);

        while (!st.empty()) {
            int u = st.back();
            st.pop_back();

            ord.push_back(u);

            for (int e = head[u]; e != -1; e = nx[e]) {
                st.push_back(to[e]);
            }
        }

        vector<Md> dp(n + 1, {0, 0});

        for (int i = (int)ord.size() - 1; i >= 0; i--) {
            int u = ord[i];

            Md cur = {0, 0};

            for (int e = head[u]; e != -1; e = nx[e]) {
                int v = to[e];
                cur = joi(cur, dp[v]);
            }

            dp[u] = { cur.sz + 1, cur.mn + 1 };
        }

        Md all = {0, 0};
        for (int r : rt) all = joi(all, dp[r]);

        int ans = (n - all.mn) / 2;
        cout << ans << "\n";
    }

    return 0;
}
