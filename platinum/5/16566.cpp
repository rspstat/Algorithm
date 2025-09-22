#include <bits/stdc++.h>
using namespace std;

int n, m, k;

struct DSU {
    vector<int> p;
    DSU(int n) : p(n+1) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }
    void unite(int x, int y) {
        x = find(x), y = find(y);
        p[x] = y;
    }
};

void solve() {
    cin >> n >> m >> k;
    vector<int> cards(m);
    for (int i = 0; i < m; ++i) cin >> cards[i];
    sort(cards.begin(), cards.end());

    DSU dsu(m);

    ostringstream out;
    while (k--) {
        int x; cin >> x;
        int idx = upper_bound(cards.begin(), cards.end(), x) - cards.begin();
        idx = dsu.find(idx);
        out << cards[idx] << '\n';
        if (idx < m-1) dsu.unite(idx, idx+1);
    }

    cout << out.str();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
