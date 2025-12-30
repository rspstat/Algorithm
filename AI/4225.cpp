#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Pt {
    double x, y;
};

double dist(Pt a, Pt b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

// 외적 계산 (반시계 방향 판별)
double cp(Pt a, Pt b, Pt c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, tc = 1;
    while (cin >> n && n) {
        vector<Pt> pts(n);
        for (int i = 0; i < n; i++) cin >> pts[i].x >> pts[i].y;

        // 볼록 껍질(Convex Hull) 구성 - Monotone Chain
        sort(pts.begin(), pts.end(), [](const Pt& a, const Pt& b) {
            return a.x < b.x || (a.x == b.x && a.y < b.y);
        });

        vector<Pt> h;
        for (int i = 0; i < n; i++) {
            while (h.size() >= 2 && cp(h[h.size() - 2], h.back(), pts[i]) <= 0) h.pop_back();
            h.push_back(pts[i]);
        }
        int low_sz = h.size();
        for (int i = n - 2; i >= 0; i--) {
            while (h.size() > low_sz && cp(h[h.size() - 2], h.back(), pts[i]) <= 0) h.pop_back();
            h.push_back(pts[i]);
        }
        h.pop_back();

        double ans = 1e18;
        int sz = h.size();

        // 각 변을 밑변으로 했을 때 가장 높은 높이를 구하고 그 중 최솟값(최소 폭) 선택
        for (int i = 0; i < sz; i++) {
            double max_h = 0;
            Pt p1 = h[i];
            Pt p2 = h[(i + 1) % sz];
            double base = dist(p1, p2);

            for (int j = 0; j < sz; j++) {
                double area = abs(cp(p1, p2, h[j]));
                max_h = max(max_h, area / base);
            }
            ans = min(ans, max_h);
        }

        cout << "Case " << tc++ << ": " << fixed << setprecision(2) << ceil(ans * 100) / 100 << '\n';
    }

    return 0;
}
