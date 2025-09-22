#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    
    vector<pair<int, int>> j(n);
    vector<int> b(k);
    
    for (int i = 0; i < n; i++) {
        cin >> j[i].first >> j[i].second;
    }
    
    for (int i = 0; i < k; i++) {
        cin >> b[i];
    }
    
    sort(j.begin(), j.end());
    sort(b.begin(), b.end());
    
    priority_queue<int> pq;
    long long ans = 0;
    int idx = 0;
    
    for (int i = 0; i < k; i++) {
        while (idx < n && j[idx].first <= b[i]) {
            pq.push(j[idx].second);
            idx++;
        }
        
        if (!pq.empty()) {
            ans += pq.top();
            pq.pop();
        }
    }
    
    cout << ans << "\n";
    
    return 0;
}
