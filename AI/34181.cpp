#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

static inline int64 floordiv(int64 a, int64 b) {
    if (b < 0) a = -a, b = -b;
    if (a >= 0) return a / b;
    return - ( ( -a + b - 1 ) / b );
}
static inline int64 ceildiv(int64 a, int64 b) {
    if (b < 0) a = -a, b = -b;
    if (a >= 0) return (a + b - 1) / b;
    return - ( (-a) / b );
}

struct Piece {
    int l, r;
    int64 a, b;
};

static inline int64 evalPiece(const Piece& p, int t) {
    return p.a * (int64)t + p.b;
}

static vector<Piece> buildPieces(int T, int w, int phi) {
    int R0 = (T + 1) / 2;
    vector<Piece> res;
    res.reserve(32);

    for (int k = 0; k <= w; k++) {
        int64 L = ceildiv((int64)k * T - phi, w);
        int64 R = floordiv((int64)(k + 1) * T - 1 - phi, w);
        if (L < 1) L = 1;
        if (R > T) R = T;
        if (L > R) continue;

        int64 tCross = ceildiv((int64)R0 + (int64)k * T - phi, w);

        int64 aLow = -(int64)2 * w;
        int64 bLow = (int64)2 * k * T + T - (int64)2 * phi;

        int64 aHigh = (int64)2 * w;
        int64 bHigh = (int64)2 * phi - (int64)2 * k * T - T;

        if (tCross <= L) {
            res.push_back({(int)L, (int)R, aHigh, bHigh});
        } else if (tCross > R) {
            res.push_back({(int)L, (int)R, aLow, bLow});
        } else {
            res.push_back({(int)L, (int)(tCross - 1), aLow, bLow});
            res.push_back({(int)tCross, (int)R, aHigh, bHigh});
        }
    }

    sort(res.begin(), res.end(), [&](const Piece& p, const Piece& q){
        if (p.l != q.l) return p.l < q.l;
        return p.r < q.r;
    });

    vector<Piece> out;
    out.reserve(res.size());
    for (auto &pc : res) {
        if (!out.empty() && out.back().r + 1 == pc.l && out.back().a == pc.a && out.back().b == pc.b) {
            out.back().r = pc.r;
        } else out.push_back(pc);
    }
    return out;
}

struct DSURollback {
    int n;
    vector<int> p, sz;
    vector<pair<int,int>> st;
    int comps;

    DSURollback(int n=0){ init(n); }

    void init(int n_) {
        n = n_;
        p.resize(n);
        sz.assign(n, 1);
        for (int i = 0; i < n; i++) p[i] = i;
        st.clear();
        comps = n;
    }

    int find(int a) {
        while (p[a] != a) a = p[a];
        return a;
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            st.push_back({-1, -1});
            return;
        }
        if (sz[a] < sz[b]) swap(a, b);
        st.push_back({b, sz[a]});
        p[b] = a;
        sz[a] += sz[b];
        comps--;
    }

    int snapshot() const { return (int)st.size(); }

    void rollback(int snap) {
        while ((int)st.size() > snap) {
            auto [b, sa] = st.back();
            st.pop_back();
            if (b == -1) continue;
            int a = p[b];
            sz[a] = sa;
            p[b] = b;
            comps++;
        }
    }
};

struct Edge { int u, v; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, T;
    cin >> N >> M >> T;
    int V = N * M;

    vector<int> w(V), phi(V);
    for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) cin >> w[i*M + j];
    for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) cin >> phi[i*M + j];

    int LIM = (T - 1) / 2;

    vector<vector<Piece>> pieces(V);
    for (int i = 0; i < V; i++) pieces[i] = buildPieces(T, w[i], phi[i]);

    vector<pair<int,int>> edges;
    edges.reserve(N*(M-1) + M*(N-1));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int u = i*M + j;
            if (j + 1 < M) edges.push_back({u, u+1});
            if (i + 1 < N) edges.push_back({u, u+M});
        }
    }

    int S = 1;
    while (S < T) S <<= 1;
    vector<vector<Edge>> seg(2 * S);

    auto addInterval = [&](int l, int r, int u, int v) {
        int L = (l - 1) + S;
        int R = (r - 1) + S;
        while (L <= R) {
            if (L & 1) seg[L++].push_back({u, v});
            if (!(R & 1)) seg[R--].push_back({u, v});
            L >>= 1;
            R >>= 1;
        }
    };

    auto addEdgeActiveIntervals = [&](int u, int v) {
        const auto &A = pieces[u];
        const auto &B = pieces[v];
        int i = 0, j = 0;
        while (i < (int)A.size() && j < (int)B.size()) {
            int l = max(A[i].l, B[j].l);
            int r = min(A[i].r, B[j].r);
            if (l <= r) {
                int64 aa = A[i].a - B[j].a;
                int64 bb = A[i].b - B[j].b;

                if (aa < 0) { aa = -aa; bb = -bb; }

                int L = l, R = r;
                bool ok = true;

                if (aa == 0) {
                    if (llabs(bb) > LIM) ok = false;
                } else {
                    int64 t1 = ceildiv(-(int64)LIM - bb, aa);
                    int64 t2 = floordiv((int64)LIM - bb, aa);
                    L = max<int64>(L, t1);
                    R = min<int64>(R, t2);
                    if (L > R) ok = false;
                }

                if (ok) addInterval(L, R, u, v);
            }
            if (A[i].r < B[j].r) i++;
            else j++;
        }
    };

    for (auto &e : edges) addEdgeActiveIntervals(e.first, e.second);

    vector<int> ans(T + 1, 0);
    DSURollback dsu(V);

    function<void(int)> dfs = [&](int node) {
        int snap = dsu.snapshot();
        for (auto &e : seg[node]) dsu.unite(e.u, e.v);

        if (node >= S) {
            int t = node - S + 1;
            if (1 <= t && t <= T) ans[t] = dsu.comps;
        } else {
            dfs(node << 1);
            dfs(node << 1 | 1);
        }
        dsu.rollback(snap);
    };

    dfs(1);

    for (int t = 1; t <= T; t++) cout << ans[t] << "\n";
    return 0;
}
