#include <iostream>

using namespace std;

int main() {
    int n = 0;
    cin >> n;

    int a, b, c = 0;
    int res = 0;

    for (int i = 0 ; i < n; i++) {
        cin >> a >> b >> c;

        if ( a < c ) {
                if ( c % a == 0 ) {
                res = (a * 100) + (c / a);
                cout << res << endl;
            }

            else {
                res = ((c % a) * 100) + (c / a + 1);
                cout << res << endl;
            }
        }

        else if ( a == c ) {
            res = (a * 100) + (c / a);
            cout << res << endl;
        }

        else if ( a > c ) {
            res = c * 100 + 1;
            cout << res <<endl;
        }
    }
    return 0;
}

// 1. h < n 
// 2. h < n && h % n == 0 
// 3. h == n
// 4. h > n
