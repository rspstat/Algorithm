#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MX = 100005;
vector<int> ch[MX];
int in_t[MX], out_t[MX];
int timer = 0;
ll bit[MX];

void dfs(int u) {
    in_t[u] = ++timer;
    for (int v : ch[u]) {
        dfs(v);
    }
    out_t[u] = timer;
}

void upd(int i, ll v, int n) {
    for (; i <= n; i += i & -i) {
        bit[i] += v;
    }
}

ll qry(int i) {
    ll ret = 0;
    for (; i > 0; i -= i & -i) {
        ret += bit[i];
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    for (int i = 1; i <= n; i++) {
        int p;
        cin >> p;
        if (p != -1) {
            ch[p].push_back(i);
        }
    }
    
    dfs(1);
    
    while (m--) {
        int cmd;
        cin >> cmd;
        
        if (cmd == 1) {
            int i;
            ll w;
            cin >> i >> w;
            
            upd(in_t[i], w, n);
            upd(out_t[i] + 1, -w, n);
        } else {
            int i;
            cin >> i;
            cout << qry(in_t[i]) << '\n';
        }
    }
    
    return 0;
}
