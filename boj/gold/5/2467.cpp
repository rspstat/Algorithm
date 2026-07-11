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
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    int l = 0, r = n - 1;
    int minv = abs(a[l] + a[r]);
    int ansl = l, ansr = r;
    
    while (l < r) {
        int sum = a[l] + a[r];
        
        if (abs(sum) < minv) {
            minv = abs(sum);
            ansl = l;
            ansr = r;
        }
        
        if (sum < 0) {
            l++;
        } else {
            r--;
        }
    }
    
    cout << a[ansl] << " " << a[ansr] << "\n";
    
    return 0;
}
