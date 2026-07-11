// 11047번 동전 0
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, k, cnt = 0;
    
    cin >> n >> k;

    vector<int> a(n);

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }  

    for (int i = n - 1; i >= 0; --i) {
        if ( k >= a[i] ) {   
            cnt += k / a[i]; 
            k %= a[i];  
        }
    }

    cout << cnt;

    return 0;
}
