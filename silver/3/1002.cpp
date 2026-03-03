#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t = 0;
    cin >> t;

    int x1, y1, r1, x2, y2, r2;

    while (t--) {
        cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;

        int d_sq = pow((x2 - x1), 2) + pow((y2 - y1), 2);
        int sum_r_sq = pow((r1 + r2), 2);
        int diff_r_sq = pow((r1 - r2), 2);

        if (d_sq == 0 && r1 == r2)  cout << -1 << '\n';
        else if (d_sq == sum_r_sq || (d_sq == diff_r_sq && d_sq != 0)) cout << 1 << '\n';
        else if (diff_r_sq < d_sq && d_sq < sum_r_sq) cout << 2 << '\n';
        else cout << 0 << '\n';
    }

    return 0;
}
