#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, s;
    cin >> n >> s;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    int l = 0, sum = 0, ans = n + 1;
    
    for (int r = 0; r < n; r++) {
        sum += a[r];
        
        while (sum >= s) {
            ans = min(ans, r - l + 1);
            sum -= a[l];
            l++;
        }
    }
    
    cout << (ans == n + 1 ? 0 : ans) << "\n";
    
    return 0;
}
