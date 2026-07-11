#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> adj(n + 1);
    vector<int> deg(n + 1, 0);
    
    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        vector<int> ord(k);
        for (int j = 0; j < k; j++) {
            cin >> ord[j];
        }
        for (int j = 0; j < k - 1; j++) {
            adj[ord[j]].push_back(ord[j + 1]);
            deg[ord[j + 1]]++;
        }
    }
    
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 0) {
            q.push(i);
        }
    }
    
    vector<int> res;
    
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        res.push_back(cur);
        
        for (int nxt : adj[cur]) {
            deg[nxt]--;
            if (deg[nxt] == 0) {
                q.push(nxt);
            }
        }
    }
    
    if (res.size() != n) {
        cout << 0 << "\n";
    } else {
        for (int x : res) {
            cout << x << "\n";
        }
    }
    
    return 0;
}
