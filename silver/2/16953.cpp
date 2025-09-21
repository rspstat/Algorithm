#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long a, b;
    cin >> a >> b;

    long long cnt = 1; // 연산 횟수 + 1 (B에서 A로 역추적)
    while (b > a) {
        if (b % 10 == 1) {        // ...1 이면 10으로 나눔
            b /= 10;
            ++cnt;
        } else if (b % 2 == 0) {  // 짝수면 2로 나눔
            b /= 2;
            ++cnt;
        } else {
            break;                // 더 이상 줄일 수 없음
        }
    }

    if (a == b) cout << cnt << '\n';
    else cout << -1 << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
