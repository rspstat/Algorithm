#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct P {
    ll x, y;
};

ll ccw(const P& a, const P& b, const P& c) {
    ll v = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (v > 0)  return 1;
    if (v < 0)  return -1;
    return 0;
}

bool inBox(const P& a, const P& b, const P& p) {
    ll minx = min(a.x, b.x), maxx = max(a.x, b.x);
    ll miny = min(a.y, b.y), maxy = max(a.y, b.y);
    return (minx <= p.x && p.x <= maxx) && (miny <= p.y && p.y <= maxy);
}

bool intersect(P a, P b, P c, P d) {
    ll ab1 = ccw(a, b, c);
    ll ab2 = ccw(a, b, d);
    ll cd1 = ccw(c, d, a);
    ll cd2 = ccw(c, d, b);

    // 일반 교차
    if (ab1 * ab2 < 0 && cd1 * cd2 < 0) return true;

    // 한쪽이라도 일직선인 경우: 박스 포함 여부로 체크
    if (ab1 == 0 && inBox(a, b, c)) return true;
    if (ab2 == 0 && inBox(a, b, d)) return true;
    if (cd1 == 0 && inBox(c, d, a)) return true;
    if (cd2 == 0 && inBox(c, d, b)) return true;

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    P a, b, c, d;
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;

    cout << (intersect(a, b, c, d) ? 1 : 0) << '\n';
    return 0;
}
