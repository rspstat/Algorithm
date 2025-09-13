#include <bits/stdc++.h>
using namespace std;

const int MX = 100000 + 1;

int n;
vector<int> g[MX];
int par[MX];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    queue<int> q;
    q.push(1);
    par[1] = 0;

    while (!q.empty()) {
        int cur = q.front(); q.pop();
        for (int nxt : g[cur]) {
            if (nxt == par[cur]) continue;
            if (par[nxt] != 0) continue;
            par[nxt] = cur;
            q.push(nxt);
        }
    }

    for (int i = 2; i <= n; i++) {
        cout << par[i] << '\n';
    }
    
    return 0;
}
