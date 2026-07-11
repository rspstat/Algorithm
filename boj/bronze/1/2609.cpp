#include <iostream>

using namespace std;


int gcd (int a, int b) {    //유클리드 호제법 최대공약수 구하기
    int c = 0;

    while (b != 0) {
        c = a % b;
        a = b;
        b = c;
    }

    return a;       // a == n, b == m;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m = 0;
    cin >> n >> m;

    int res = 0;
    res = gcd(n, m);    //유클리드 호제법 최대공약수 구하기

    //최소공배수 구하기
    int lcm = 0;
    lcm = n * m / res;

    cout << res << "\n" << lcm;

    return 0;
}
