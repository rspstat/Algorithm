#include <bits/stdc++.h>
using namespace std;

vector<int> p, candy;

int find(int x) {
    return p[x] == x ? x : p[x] = find(p[x]);
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) p[y] = x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, k;
    cin >> n >> m >> k;
    
    p.resize(n + 1);
    candy.resize(n + 1);
    
    iota(p.begin(), p.end(), 0);
    
    for (int i = 1; i <= n; i++) {
        cin >> candy[i];
    }
    
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        unite(a, b);
    }
    
    // 각 그룹별 사탕 개수와 아이 수 계산
    map<int, pair<int, int>> groups; // {root: {candy_sum, child_count}}
    
    for (int i = 1; i <= n; i++) {
        int root = find(i);
        groups[root].first += candy[i];
        groups[root].second++;
    }
    
    // 냅색 DP
    vector<int> dp(k, 0);
    
    for (auto& [root, info] : groups) {
        int weight = info.second; // 아이 수
        int value = info.first;   // 사탕 수
        
        for (int j = k - 1; j >= weight; j--) {
            dp[j] = max(dp[j], dp[j - weight] + value);
        }
    }
    
    cout << dp[k - 1] << '\n';
    
    return 0;
}
