#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int T;  // 테스트 케이스
    cin >> T;

    while (T--) {
        int n, m;
        cin >> n >> m;

        cout << n - 1 << '\n';

        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
        }
    }

    return 0;
}
