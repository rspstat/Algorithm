#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
int visited[MAXN];
struct Boomerang {
    int u, v, w;
};
vector<Boomerang> ans;

bool dfs(int u, int p, int depth) {
    visited[u] = depth;
    vector<int> friends;

    for (int v : adj[u]) {
        if (v == p) continue;

        if (visited[v]) {
            if (visited[v] < visited[u]) {
                friends.push_back(v);
            }
        } else {
            if (dfs(v, u, depth + 1)) {
                friends.push_back(v);
            }
        }
    }

    for (size_t i = 0; i + 1 < friends.size(); i += 2) {
        ans.push_back({friends[i], u, friends[i + 1]});
    }

    if (friends.size() % 2 == 1) {
        if (p != 0) {
            ans.push_back({friends.back(), u, p});
            return false;
        }
    }

    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i, 0, 1);
        }
    }

    cout << ans.size() << "\n";
    for (const auto& b : ans) {
        cout << b.u << " " << b.v << " " << b.w << "\n";
    }

    return 0;
}
