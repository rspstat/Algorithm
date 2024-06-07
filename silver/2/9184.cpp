#include <iostream>

using namespace std;

int dp[21][21][21] = {0, }; //dp 초기 배열

int w(int a, int b, int c);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int a, b, c;

    while (1) {
        cin >> a >> b >> c;
        if ( a == -1 && b == -1 && c == -1 ) {
            break;
        }
        cout << "w(" << a << ", " << b << ", " << c << ") = " << w(a, b, c) << "\n";     
    }
}

int w(int a, int b, int c) {    //반환한다는게 수학적으로 값을 뱉는거 준다는 뜻임;; 이제 이해함
    if ( a <= 0 || b <= 0 || c <= 0 ) 
        return 1;

    else if ( a > 20 || b > 20 || c > 20 ) 
        return w(20, 20, 20);

    else if ( dp[a][b][c] != 0 ) 
        return dp[a][b][c];

    else if ( a < b && b < c ) 
        dp[a][b][c] = w(a, b, c-1) + w(a, b-1, c-1) - w(a, b-1, c);

    else 
        dp[a][b][c] = w(a-1, b, c) + w(a-1, b-1, c) + w(a-1, b, c-1) - w(a-1, b-1, c-1);

    return dp[a][b][c];
}   //else-if 마다 return 안하는게 나음...

// if a <= 0 or b <= 0 or c <= 0, then w(a, b, c) returns: 1

// if a > 20 or b > 20 or c > 20, then w(a, b, c) returns: w(20, 20, 20)

// if a < b and b < c, then w(a, b, c) returns: w(a, b, c-1) + w(a, b-1, c-1) - w(a, b-1, c)

// otherwise it returns: w(a-1, b, c) + w(a-1, b-1, c) + w(a-1, b, c-1) - w(a-1, b-1, c-1)
