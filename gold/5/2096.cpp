#include <bits/stdc++.h>
using namespace std;

int n;

void solve() {
    cin >> n;
    int a, b, c;

    int maxdp[3] = {0, 0, 0};
    int mindp[3] = {0, 0, 0};

    // 첫 행 초기화
    cin >> a >> b >> c;
    maxdp[0] = mindp[0] = a;
    maxdp[1] = mindp[1] = b;
    maxdp[2] = mindp[2] = c;

    for (int i = 1; i < n; ++i) {
        cin >> a >> b >> c;

        int nmax0 = max(maxdp[0], maxdp[1]) + a;
        int nmax1 = max({maxdp[0], maxdp[1], maxdp[2]}) + b;
        int nmax2 = max(maxdp[1], maxdp[2]) + c;

        int nmin0 = min(mindp[0], mindp[1]) + a;
        int nmin1 = min({mindp[0], mindp[1], mindp[2]}) + b;
        int nmin2 = min(mindp[1], mindp[2]) + c;

        maxdp[0] = nmax0; maxdp[1] = nmax1; maxdp[2] = nmax2;
        mindp[0] = nmin0; mindp[1] = nmin1; mindp[2] = nmin2;
    }

    int maxAns = max({maxdp[0], maxdp[1], maxdp[2]});
    int minAns = min({mindp[0], mindp[1], mindp[2]});
    cout << maxAns << ' ' << minAns << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
