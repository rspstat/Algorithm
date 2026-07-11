#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const { return w < other.w; }
};

struct DSU {
    vector<int> p;
    DSU(int n) : p(n) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        p[b] = a;
        return true;
    }
};

void solve() {
    int n; cin >> n;
    vector<array<int,2>> X(n), Y(n), Z(n);
    for (int i = 0; i < n; ++i) {
        int x, y, z; cin >> x >> y >> z;
        X[i] = {x, i};
        Y[i] = {y, i};
        Z[i] = {z, i};
    }
    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());
    sort(Z.begin(), Z.end());

    vector<Edge> edges;
    edges.reserve(3 * (n - 1));
    for (int i = 0; i < n - 1; ++i) {
        edges.push_back({X[i][1], X[i+1][1], abs(X[i+1][0] - X[i][0])});
        edges.push_back({Y[i][1], Y[i+1][1], abs(Y[i+1][0] - Y[i][0])});
        edges.push_back({Z[i][1], Z[i+1][1], abs(Z[i+1][0] - Z[i][0])});
    }

    sort(edges.begin(), edges.end());
    DSU dsu(n);
    long long ans = 0;
    int cnt = 0;
    for (auto &e : edges) {
        if (dsu.unite(e.u, e.v)) {
            ans += e.w;
            if (++cnt == n - 1) break;
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
