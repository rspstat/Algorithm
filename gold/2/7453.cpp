#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    vector<int> a(n), b(n), c(n), d(n);
    
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i] >> c[i] >> d[i];
    }
    
    vector<int> ab;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ab.push_back(a[i] + b[j]);
        }
    }
    
    sort(ab.begin(), ab.end());
    
    long long cnt = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int t = -(c[i] + d[j]);
            auto lo = lower_bound(ab.begin(), ab.end(), t);
            auto hi = upper_bound(ab.begin(), ab.end(), t);
            cnt += hi - lo;
        }
    }
    
    cout << cnt << "\n";
    
    return 0;
}
