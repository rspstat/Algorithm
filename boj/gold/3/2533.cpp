#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<int> adj[1000001];
int dp[1000001][2];

void dfs(int cur, int prev) {
    dp[cur][0] = 0;
    dp[cur][1] = 1;

    for (int nxt : adj[cur]) {
        if (nxt == prev) continue;
        dfs(nxt, cur);
        
        // cur가 얼리어답터가 아니면 자식은 무조건 얼리어답터여야 함
        dp[cur][0] += dp[nxt][1];
        
        // cur가 얼리어답터면 자식은 상관없음 (최소값 선택)
        dp[cur][1] += min(dp[nxt][0], dp[nxt][1]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, -1);

    cout << min(dp[1][0], dp[1][1]);

    return 0;
}
