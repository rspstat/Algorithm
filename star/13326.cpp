#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x;
    long long y;
};

static inline long long dist2(const Point& a, const Point& b) {
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;
    return dx * dx + dy * dy;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Point> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y;
    }

    int t1 = 0, t2 = 1;
    long long bestD = dist2(p[t1], p[t2]);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            long long d = dist2(p[i], p[j]);
            if (d > bestD) {
                bestD = d;
                t1 = i;
                t2 = j;
            }
        }
    }

    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);

    sort(ord.begin(), ord.end(), [&](int a, int b) {
        long long da = dist2(p[t1], p[a]);
        long long db = dist2(p[t1], p[b]);
        if (da != db) return da < db;
        if (p[a].x != p[b].x) return p[a].x < p[b].x;
        return p[a].y < p[b].y;
    });

    vector<long long> suf(n + 1, 0);

    for (int i = n - 1; i >= 0; i--) {
        long long cur = suf[i + 1];
        int ai = ord[i];
        for (int j = i + 1; j < n; j++) {
            cur = max(cur, dist2(p[ai], p[ord[j]]));
        }
        suf[i] = cur;
    }

    long long pre = 0;
    long double ans = 1e100L;

    for (int i = 1; i <= n - 1; i++) {
        int v = ord[i - 1];
        for (int j = 0; j < i - 1; j++) {
            pre = max(pre, dist2(p[v], p[ord[j]]));
        }
        long double cur = sqrt((long double)pre) + sqrt((long double)suf[i]);
        if (cur < ans) ans = cur;
    }

    cout << fixed << setprecision(10) << (double)ans << "\n";
    return 0;
}
