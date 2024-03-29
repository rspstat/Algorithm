#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int n, m = 0;
    cin >> n >> m;

    int res = 1;

    for (int i = 0; i < m; i++) {
        res *= n;
        n--;
    }

    int res2 = 1;
    
    for (int i = 1; i <= m; i++) {
        res2 *= i;
    }

    int res3 = 0;
    res3 = res / res2;

    cout << res3;

    return 0;
}
