#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int n, m;
vector<int> adj[1005];
int match[1005]; // 오른쪽 그룹(도착점)에 매칭된 왼쪽 그룹(시작점) 번호
bool vis[1005];

bool dfs(int cur) {
    for (int nxt : adj[cur]) {
        if (vis[nxt]) continue;
        vis[nxt] = true;
        // nxt가 매칭되지 않았거나, 이미 매칭된 노드가 다른 곳으로 이동 가능하면 연결
        if (match[nxt] == -1 || dfs(match[nxt])) {
            match[nxt] = cur;
            return true;
        }
    }
    return false;
}

void solve() {
    cin >> n >> m;
    
    for (int i = 0; i < n; i++) adj[i].clear();
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        // u(나가는 그룹) -> v(들어오는 그룹) 단방향 간선
        adj[u].push_back(v);
    }

    int ans = 0;
    memset(match, -1, sizeof(match));

    for (int i = 0; i < n; i++) {
        memset(vis, 0, sizeof(vis));
        if (dfs(i)) ans++;
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
