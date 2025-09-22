#include <bits/stdc++.h>
using namespace std;

int n, w[16][16];
int dp[16][1<<16];
const int INF = 1e9;

int tsp(int cur, int mask) {
    // 모든 도시 방문 완료
    if (mask == (1 << n) - 1) {
        return w[cur][0] ? w[cur][0] : INF;
    }
    
    // 메모이제이션
    int& ret = dp[cur][mask];
    if (ret != -1) return ret;
    
    ret = INF;
    
    // 다음 도시 선택
    for (int next = 0; next < n; next++) {
        if (mask & (1 << next)) continue;  // 이미 방문
        if (!w[cur][next]) continue;       // 길이 없음
        
        ret = min(ret, w[cur][next] + tsp(next, mask | (1 << next)));
    }
    
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> w[i][j];
        }
    }
    
    memset(dp, -1, sizeof(dp));
    
    cout << tsp(0, 1) << '\n';
    
    return 0;
}
