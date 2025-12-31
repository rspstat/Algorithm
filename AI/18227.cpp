#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int n, c, q;
vector<int> adj[200005];
int d[200005], in[200005], out[200005];
int tmr = 0;
ll bit[200005];

void u(int i, int v) {
    while (i <= n) {
        bit[i] += v;
        i += i & -i;
    }
}

ll qry(int i) {
    ll ret = 0;
    while (i > 0) {
        ret += bit[i];
        i -= i & -i;
    }
    return ret;
}

void dfs(int cur, int prev, int dep) {
    d[cur] = dep;
    in[cur] = ++tmr;
    for (int nxt : adj[cur]) {
        if (nxt == prev) continue;
        dfs(nxt, cur, dep + 1);
    }
    out[cur] = tmr;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> c;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(c, -1, 1);

    cin >> q;
    while (q--) {
        int op, a;
        cin >> op >> a;
        if (op == 1) {
            u(in[a], 1);
        } else {
            ll cnt = qry(out[a]) - qry(in[a] - 1);
            cout << cnt * d[a] << '\n';
        }
    }

    return 0;
}
