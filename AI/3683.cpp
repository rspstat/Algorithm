#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Voter {
    string keep, drop;
};

int c, d, v;
vector<Voter> cat_lovers, dog_lovers;
vector<int> adj[505];
int match[505];
bool vis[505];

// 이분 매칭 DFS
bool dfs(int cur) {
    for (int nxt : adj[cur]) {
        if (vis[nxt]) continue;
        vis[nxt] = true;

        if (match[nxt] == -1 || dfs(match[nxt])) {
            match[nxt] = cur;
            return true;
        }
    }
    return false;
}

void solve() {
    cin >> c >> d >> v;

    cat_lovers.clear();
    dog_lovers.clear();
    for (int i = 0; i < v; i++) {
        string k, dr;
        cin >> k >> dr;
        // 고양이를 좋아하는 사람(C로 시작)과 개를 좋아하는 사람(D로 시작) 분리
        if (k[0] == 'C') cat_lovers.push_back({k, dr});
        else dog_lovers.push_back({k, dr});
    }

    // 그래프 초기화
    int n = cat_lovers.size();
    int m = dog_lovers.size();
    for (int i = 0; i < n; i++) adj[i].clear();

    // 간선 연결 (모순이 발생하면 연결)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // Cat Lover가 살리려는 고양이를 Dog Lover가 버리려 하거나
            // Cat Lover가 버리려는 개를 Dog Lover가 살리려 하면 모순
            if (cat_lovers[i].keep == dog_lovers[j].drop || 
                cat_lovers[i].drop == dog_lovers[j].keep) {
                adj[i].push_back(j);
            }
        }
    }

    // 최대 매칭 구하기
    int matched_cnt = 0;
    fill(match, match + m, -1);
    for (int i = 0; i < n; i++) {
        fill(vis, vis + m, false);
        if (dfs(i)) matched_cnt++;
    }

    // 최대 독립 집합 = 전체 정점 - 최대 매칭
    cout << v - matched_cnt << '\n';
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
