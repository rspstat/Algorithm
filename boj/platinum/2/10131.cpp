#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> c(n + 1);
    for (int i = 1; i <= n; i++) cin >> c[i];

    vector<vector<int>> g(n + 1);
    g.reserve(n + 1);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    // 1) parent + order (iterative)
    vector<int> parent(n + 1, 0);
    vector<int> order;
    order.reserve(n);

    {
        stack<int> st;
        st.push(1);
        parent[1] = -1;

        while (!st.empty()) {
            int u = st.top();
            st.pop();
            order.push_back(u);

            for (int v : g[u]) {
                if (v == parent[u]) continue;
                parent[v] = u;
                st.push(v);
            }
        }
    }

    // 2) children lists
    vector<vector<int>> child(n + 1);
    for (int v = 2; v <= n; v++) {
        child[parent[v]].push_back(v);
    }

    // 3) postorder DP
    vector<int> sz(n + 1, 1);
    vector<long long> best(n + 1, 0);

    for (int idx = (int)order.size() - 1; idx >= 0; idx--) {
        int u = order[idx];

        // subtree size
        int s = 1;
        for (int v : child[u]) s += sz[v];
        sz[u] = s;

        // root installs at the end => ignore c[1] inside DP
        long long base = (u == 1 ? 0LL : c[u]);

        // sort children by key = p - q = 2*sz[v] - (1 + best[v])
        auto &ch = child[u];
        sort(ch.begin(), ch.end(), [&](int a, int b) {
            long long ka = 2LL * sz[a] - (1LL + best[a]);
            long long kb = 2LL * sz[b] - (1LL + best[b]);
            if (ka != kb) return ka < kb;
            return a < b;
        });

        long long cur = 0;
        long long mx = base;

        for (int v : ch) {
            mx = max(mx, cur + 1LL + best[v]);
            cur += 2LL * sz[v];
        }

        best[u] = mx;
    }

    long long tourEnd = 2LL * (n - 1);
    long long answer = max(best[1], tourEnd + c[1]);
    cout << answer << "\n";
    return 0;
}
