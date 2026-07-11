#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    sort(a.begin(), a.end());
    
    long long minv = 3e9;
    vector<long long> ans(3);
    
    for (int i = 0; i < n - 2; i++) {
        int l = i + 1, r = n - 1;
        
        while (l < r) {
            long long sum = a[i] + a[l] + a[r];
            
            if (abs(sum) < minv) {
                minv = abs(sum);
                ans = {a[i], a[l], a[r]};
            }
            
            if (sum < 0) {
                l++;
            } else {
                r--;
            }
        }
    }
    
    cout << ans[0] << " " << ans[1] << " " << ans[2] << "\n";
    
    return 0;
}
