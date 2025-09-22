#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        vector<int> a(n + 1);
        vector<bool> vis(n + 1, false);
        vector<bool> fin(n + 1, false);
        
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        
        int cnt = 0;
        
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) {
                int cur = i;
                
                while (!vis[cur]) {
                    vis[cur] = true;
                    cur = a[cur];
                }
                
                if (!fin[cur]) {
                    int cycle = cur;
                    do {
                        cnt++;
                        fin[cycle] = true;
                        cycle = a[cycle];
                    } while (cycle != cur);
                }
                
                cur = i;
                while (!fin[cur]) {
                    fin[cur] = true;
                    cur = a[cur];
                }
            }
        }
        
        cout << n - cnt << "\n";
    }
    
    return 0;
}
