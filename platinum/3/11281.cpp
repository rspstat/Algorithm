#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    int V = 2 * n;
    vector<vector<int>> g(V), rg(V), ord;
    vector<int> st, comp(V, -1), vis(V, 0);

    auto id = [&](int x) {
        int v = abs(x) - 1;
        // 2*v:  x_i (true), 2*v^1: ~x_i (false)
        return x > 0 ? (2 * v) : (2 * v + 1);
    };
    auto neg = [&](int u) { return u ^ 1; };

    for (int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        int ua = id(a), ub = id(b);
        int na = neg(ua), nb = neg(ub);
        // (~a -> b), (~b -> a)
        g[na].push_back(ub);
        g[nb].push_back(ua);
        rg[ub].push_back(na);
        rg[ua].push_back(nb);
    }

    // 1st pass (order)
    vector<int> order;
    function<void(int)> dfs1 = [&](int u) {
        vis[u] = 1;
        for (int v : g[u]) if (!vis[v]) dfs1(v);
        order.push_back(u);
    };
    for (int i = 0; i < V; ++i) if (!vis[i]) dfs1(i);

    // 2nd pass (assign components)
    int cid = 0;
    function<void(int)> dfs2 = [&](int u) {
        comp[u] = cid;
        for (int v : rg[u]) if (comp[v] == -1) dfs2(v);
    };
    for (int i = V - 1; i >= 0; --i) {
        int u = order[i];
        if (comp[u] == -1) { dfs2(u); ++cid; }
    }

    // Check satisfiable
    for (int i = 0; i < n; ++i) {
        if (comp[2*i] == comp[2*i+1]) {
            cout << 0 << '\n';
            return 0;
        }
    }

    // Build assignment: true if comp(true) > comp(false)
    vector<int> ans(n, 0);
    for (int i = 0; i < n; ++i) ans[i] = (comp[2*i] > comp[2*i+1]);

    cout << 1 << '\n';
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << (i+1==n?'\n':' ');
    }
    return 0;
}
