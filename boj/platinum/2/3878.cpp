#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Pt {
    long long x, y;
    bool operator<(const Pt& o) const {
        if (x != o.x) return x < o.x;
        return y < o.y;
    }
};

int ccw(Pt a, Pt b, Pt c) {
    long long val = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (val > 0) return 1;
    if (val < 0) return -1;
    return 0;
}

// 선분 교차 판별 (끝점 포함)
bool is_cross(Pt a, Pt b, Pt c, Pt d) {
    int ab = ccw(a, b, c) * ccw(a, b, d);
    int cd = ccw(c, d, a) * ccw(c, d, b);
    if (ab == 0 && cd == 0) {
        if (b < a) swap(a, b);
        if (d < c) swap(c, d);
        return !(b < c || d < a);
    }
    return ab <= 0 && cd <= 0;
}

// 점이 볼록 다각형 내부에 있는지 판별
bool is_inside(const vector<Pt>& h, Pt p) {
    if (h.size() == 1) return h[0].x == p.x && h[0].y == p.y;
    if (h.size() == 2) return is_cross(h[0], h[1], p, p);
    
    int dir = ccw(h[0], h[1], p);
    for (int i = 1; i < h.size(); i++) {
        int nxt = (i + 1) % h.size();
        if (ccw(h[i], h[nxt], p) * dir <= 0) return false; // 경계 포함시 <= 0, 미포함시 < 0 (여기선 겹치면 NO이므로 포함)
    }
    return true;
}

vector<Pt> get_hull(vector<Pt>& p) {
    int n = p.size();
    if (n <= 2) return p;
    sort(p.begin(), p.end());
    vector<Pt> h;
    for (int i = 0; i < n; i++) {
        while (h.size() >= 2 && ccw(h[h.size() - 2], h.back(), p[i]) <= 0) h.pop_back();
        h.push_back(p[i]);
    }
    int s = h.size();
    for (int i = n - 2; i >= 0; i--) {
        while (h.size() > s && ccw(h[h.size() - 2], h.back(), p[i]) <= 0) h.pop_back();
        h.push_back(p[i]);
    }
    h.pop_back();
    return h;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<Pt> b(n), w(m);
    for (int i = 0; i < n; i++) cin >> b[i].x >> b[i].y;
    for (int i = 0; i < m; i++) cin >> w[i].x >> w[i].y;

    vector<Pt> hb = get_hull(b);
    vector<Pt> hw = get_hull(w);

    // 1. 점이 상대 다각형 내부에 있는지 확인
    for (auto& p : hb) {
        if (is_inside(hw, p)) { cout << "NO\n"; return; }
    }
    for (auto& p : hw) {
        if (is_inside(hb, p)) { cout << "NO\n"; return; }
    }

    // 2. 선분끼리 교차하는지 확인
    int bs = hb.size();
    int ws = hw.size();
    if (bs > 1 && ws > 1) {
        for (int i = 0; i < bs; i++) {
            for (int j = 0; j < ws; j++) {
                if (is_cross(hb[i], hb[(i + 1) % bs], hw[j], hw[(j + 1) % ws])) {
                    cout << "NO\n";
                    return;
                }
            }
        }
    }

    cout << "YES\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
