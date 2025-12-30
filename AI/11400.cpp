#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int v, e, tmr;
vector<int> adj[100001];
int disc[100001], low[100001];
vector<pair<int, int>> ans;

void dfs(int cur, int prev) {
    disc[cur] = low[cur] = ++tmr;

    for (int nxt : adj[cur]) {
        if (nxt == prev) continue;

        if (disc[nxt]) {
            low[cur] = min(low[cur], disc[nxt]);
        } else {
            dfs(nxt, cur);
            low[cur] = min(low[cur], low[nxt]);
            // 자식 정점이 현재 정점보다 이전으로 갈 수 없으면 단절선
            if (low[nxt] > disc[cur]) ans.push_back({min(cur, nxt), max(cur, nxt)});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> v >> e;
    while (e--) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int i = 1; i <= v; i++) {
        if (!disc[i]) dfs(i, 0);
    }

    sort(ans.begin(), ans.end());

    cout << ans.size() << '\n';
    for (auto& p : ans) cout << p.first << " " << p.second << '\n';

    return 0;
}
