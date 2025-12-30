#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

struct Pt {
    ll x, y;
    bool operator<(const Pt& o) const {
        if (x != o.x) return x < o.x;
        return y < o.y;
    }
    Pt operator-(const Pt& o) const {
        return {x - o.x, y - o.y};
    }
};

ll dist(Pt a, Pt b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

ll cp(Pt a, Pt b) {
    return a.x * b.y - a.y * b.x;
}

// 반시계 방향 판별 (CCW)
ll ccw(Pt a, Pt b, Pt c) {
    return cp(b - a, c - a);
}

void solve() {
    int n;
    cin >> n;
    vector<Pt> p(n);
    for (int i = 0; i < n; i++) cin >> p[i].x >> p[i].y;

    sort(p.begin(), p.end());

    // 1. 볼록 껍질 구성 (Monotone Chain)
    vector<Pt> h;
    // Lower Hull
    for (int i = 0; i < n; i++) {
        while (h.size() >= 2 && ccw(h[h.size() - 2], h.back(), p[i]) <= 0) h.pop_back();
        h.push_back(p[i]);
    }
    // Upper Hull
    int s = h.size();
    for (int i = n - 2; i >= 0; i--) {
        while (h.size() > s && ccw(h[h.size() - 2], h.back(), p[i]) <= 0) h.pop_back();
        h.push_back(p[i]);
    }
    if (h.size() > 1) h.pop_back();

    int sz = h.size();
    if (sz == 2) {
        cout << h[0].x << " " << h[0].y << " " << h[1].x << " " << h[1].y << '\n';
        return;
    }

    // 2. 회전하는 캘리퍼스 (Rotating Calipers)
    int j = 1;
    ll max_d = 0;
    Pt ans1 = h[0], ans2 = h[1];

    for (int i = 0; i < sz; i++) {
        int ni = (i + 1) % sz;
        // 외적값이 양수라면(각도가 벌어지는 동안) j를 전진
        while (cp(h[ni] - h[i], h[(j + 1) % sz] - h[j]) > 0) {
            ll d = dist(h[i], h[j]);
            if (d > max_d) {
                max_d = d;
                ans1 = h[i];
                ans2 = h[j];
            }
            j = (j + 1) % sz;
        }
        
        // 현재 멈춘 위치에서도 거리 갱신 확인
        ll d = dist(h[i], h[j]);
        if (d > max_d) {
            max_d = d;
            ans1 = h[i];
            ans2 = h[j];
        }
    }
    
    cout << ans1.x << " " << ans1.y << " " << ans2.x << " " << ans2.y << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
