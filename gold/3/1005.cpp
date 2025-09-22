#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n, k;
        cin >> n >> k;
        
        vector<int> d(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> d[i];
        }
        
        vector<vector<int>> adj(n + 1);
        vector<int> deg(n + 1, 0);
        
        for (int i = 0; i < k; i++) {
            int x, y;
            cin >> x >> y;
            adj[x].push_back(y);
            deg[y]++;
        }
        
        int w;
        cin >> w;
        
        vector<int> time(n + 1);
        queue<int> q;
        
        for (int i = 1; i <= n; i++) {
            if (deg[i] == 0) {
                q.push(i);
                time[i] = d[i];
            }
        }
        
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            
            for (int nxt : adj[cur]) {
                time[nxt] = max(time[nxt], time[cur] + d[nxt]);
                deg[nxt]--;
                if (deg[nxt] == 0) {
                    q.push(nxt);
                }
            }
        }
        
        cout << time[w] << "\n";
    }
    
    return 0;
}
