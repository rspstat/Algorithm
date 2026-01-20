#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 1005;
const int MAXV = 1005;
const int INF = 1e9;

int N, K;
vector<int> adj[MAXN];
int val[MAXN];
bool visited[MAXN];
int bit[MAXV];
int min_inversions = INF;

void update(int idx, int diff) {
    while (idx < MAXV) {
        bit[idx] += diff;
        idx += (idx & -idx);
    }
}

int query(int idx) {
    int sum = 0;
    while (idx > 0) {
        sum += bit[idx];
        idx -= (idx & -idx);
    }
    return sum;
}

void dfs(int u, int current_len, int current_inv) {
    if (current_inv >= min_inversions) return;

    if (current_len >= K) {
        min_inversions = min(min_inversions, current_inv);
    }

    visited[u] = true;
    update(val[u], 1);

    for (int v : adj[u]) {
        if (!visited[v]) {
            int greater_count = current_len - query(val[v]);
            dfs(v, current_len + 1, current_inv + greater_count);
        }
    }

    update(val[u], -1);
    visited[u] = false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> N >> K)) return 0;

    for (int i = 0; i < N; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= N; i++) {
        cin >> val[i];
    }

    for (int i = 1; i <= N; i++) {
        visited[i] = true;
        update(val[i], 1);
        
        if (1 >= K) min_inversions = min(min_inversions, 0);

        for (int v : adj[i]) {
            if (!visited[v]) {
                int greater_count = 1 - query(val[v]);
                dfs(v, 2, greater_count);
            }
        }
        
        update(val[i], -1);
        visited[i] = false;
    }

    if (min_inversions == INF) {
        cout << -1 << endl;
    } else {
        cout << min_inversions << endl;
    }

    return 0;
}
