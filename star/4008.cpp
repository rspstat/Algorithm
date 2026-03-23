#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

struct Line {
    ll m, k;
    ll eval(ll x) { return m * x + k; }
};

int n, ptr = 0;
ll a, b, c;
ll s[1000005], dp[1000005];
vector<Line> hull;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> a >> b >> c;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        s[i] = s[i - 1] + x;
    }

    // 초기값: j=0일 때의 직선 (m=0, k=0)
    hull.push_back({0, 0});

    for (int i = 1; i <= n; i++) {
        ll cur_x = s[i];

        // 쿼리 x가 증가하므로 포인터를 이동하며 최적 직선 탐색
        ptr = min(ptr, (int)hull.size() - 1);
        while (ptr + 1 < hull.size() && hull[ptr].eval(cur_x) <= hull[ptr + 1].eval(cur_x)) {
            ptr++;
        }

        dp[i] = hull[ptr].eval(cur_x) + a * cur_x * cur_x + b * cur_x + c;

        // 새로운 직선 추가: 기울기 -2aS[i], 절편 DP[i] + aS[i]^2 - bS[i]
        Line cur_line = {-2 * a * cur_x, dp[i] + a * cur_x * cur_x - b * cur_x};

        // CHT: 교점을 비교하여 불필요한 직선 제거 (__int128로 오버플로우 방지)
        while (hull.size() >= 2) {
            Line& l1 = hull[hull.size() - 2];
            Line& l2 = hull.back();
            if ((l1.k - l2.k) * (__int128)(cur_line.m - l2.m) >= (l2.k - cur_line.k) * (__int128)(l2.m - l1.m)) {
                hull.pop_back();
            } else {
                break;
            }
        }
        hull.push_back(cur_line);
    }

    cout << dp[n];

    return 0;
}
