#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

struct Line {
    ll m, k;
    ll eval(ll x) { return m * x + k; }
};

int n;
ll a[100005], b[100005];
ll dp[100005];
vector<Line> hull;
int ptr = 0; // Monotone CHT를 위한 포인터

// 두 직선의 교점의 x좌표 계산
double intersect(Line& l1, Line& l2) {
    return (double)(l2.k - l1.k) / (l1.m - l2.m);
}

void add_line(ll m, ll k) {
    Line new_line = {m, k};
    // 교점 위치를 비교하여 불필요한 직선 제거 (Convex Hull 유지)
    while (hull.size() >= 2) {
        if (intersect(hull[hull.size() - 2], hull.back()) >= intersect(hull.back(), new_line)) {
            hull.pop_back();
        } else {
            break;
        }
    }
    hull.push_back(new_line);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    // 초기값: 1번 나무는 비용 0으로 시작 (이미 서 있음, 자르는 비용은 0부터 누적)
    // 점화식: dp[i] = min(dp[j] + b[j] * a[i])
    // 직선: 기울기 b[j], 절편 dp[j]
    
    dp[1] = 0;
    add_line(b[1], dp[1]);

    for (int i = 2; i <= n; i++) {
        // Query x값(a[i])이 증가하므로 포인터를 오른쪽으로만 이동
        while (ptr + 1 < hull.size() && hull[ptr].eval(a[i]) >= hull[ptr + 1].eval(a[i])) {
            ptr++;
        }

        dp[i] = hull[ptr].eval(a[i]);
        add_line(b[i], dp[i]);
    }

    cout << dp[n];

    return 0;
}
