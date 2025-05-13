#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int gcd(int a, int b) { // 최대 공약수
    if ( b == 0 ) {
        return a;
    }

    else {
        return gcd(b, a % b);
    }
}

int lcm(int a, int b) { // 최소 공배수
    return (a * b) / gcd(a, b);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t = 0;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int m, n, x, y;
        int res = -1;
        cin >> m >> n >> x >> y;
        int maxi = lcm(m, n);

        for (int j = x; j <= maxi; j+=m) {
            int ny = j % n; // y값 갱신

            if ( ny ==  0 )
                ny = n;

            if ( ny == y ) {
                res = j;
                break;
            }
        }

        cout << res << "\n";
    }

    return 0;
}
