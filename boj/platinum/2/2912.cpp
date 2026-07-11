#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

int n, c, m;
int a[300005];
vector<int> p[10005]; // 각 색상별 등장 인덱스 저장

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> c;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        p[a[i]].push_back(i);
    }

    cin >> m;
    while (m--) {
        int l, r;
        cin >> l >> r;

        int th = (r - l + 1) / 2;
        int ans = -1;

        // 랜덤으로 20번 정도 샘플링하여 후보 확인
        for (int k = 0; k < 20; k++) {
            int idx = rand() % (r - l + 1) + l;
            int clr = a[idx];

            // 해당 색상이 구간 [l, r]에 몇 번 등장하는지 이분 탐색으로 계산
            int cnt = upper_bound(p[clr].begin(), p[clr].end(), r) 
                    - lower_bound(p[clr].begin(), p[clr].end(), l);

            if (cnt > th) {
                ans = clr;
                break;
            }
        }

        if (ans != -1) cout << "yes " << ans << '\n';
        else cout << "no\n";
    }

    return 0;
}
