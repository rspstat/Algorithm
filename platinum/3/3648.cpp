#include <bits/stdc++.h>
using namespace std;

class TwoSAT {
    int n;
    vector<vector<int>> g, rg;
    vector<int> comp, order;
    vector<char> used;

    int var(int x) const { return x > 0 ? (x - 1) << 1 : ((-x - 1) << 1) | 1; }
    int neg(int v) const { return v ^ 1; }

    void addImplication(int u, int v) {
        g[u].push_back(v);
        rg[v].push_back(u);
    }

    void dfs1(int v) {
        used[v] = 1;
        for (int to : g[v]) if (!used[to]) dfs1(to);
        order.push_back(v);
    }

    void dfs2(int v, int c) {
        comp[v] = c;
        for (int to : rg[v]) if (comp[to] == -1) dfs2(to, c);
    }

public:
    explicit TwoSAT(int variables) : n(variables), g(2 * n), rg(2 * n) {}

    void addClause(int a, int b) {
        addImplication(neg(var(a)), var(b));
        addImplication(neg(var(b)), var(a));
    }

    void forceTrue(int a) { addClause(a, a); }

    bool satisfiable() {
        int N = 2 * n;
        used.assign(N, 0);
        order.clear();
        for (int i = 0; i < N; ++i) if (!used[i]) dfs1(i);
        comp.assign(N, -1);
        for (int i = N - 1, c = 0; i >= 0; --i)
            if (comp[order[i]] == -1) dfs2(order[i], c++);

        for (int i = 1; i <= n; ++i)
            if (comp[var(i)] == comp[var(-i)]) return false;
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    while (cin >> n >> m) {
        TwoSAT sat(n);
        sat.forceTrue(1);
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            sat.addClause(a, b);
        }
        cout << (sat.satisfiable() ? "yes\n" : "no\n");
    }
    return 0;
}
