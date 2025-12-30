#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

typedef long long ll;

struct Pt {
    ll x, y;
    bool operator<(const Pt& o) const {
        if (x == o.x) return y < o.y;
        return x < o.x;
    }
    bool operator<=(const Pt& o) const {
        if (x == o.x) return y <= o.y;
        return x < o.x;
    }
    bool operator==(const Pt& o) const {
        return x == o.x && y == o.y;
    }
};

int ccw(Pt a, Pt b, Pt c) {
    ll val = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (val > 0) return 1;
    if (val < 0) return -1;
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    Pt p1, p2, p3, p4;
    cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y >> p4.x >> p4.y;

    int c1 = ccw(p1, p2, p3);
    int c2 = ccw(p1, p2, p4);
    int c3 = ccw(p3, p4, p1);
    int c4 = ccw(p3, p4, p2);

    // 1. 네 점이 모두 일직선 상에 있는 경우
    if (c1 == 0 && c2 == 0 && c3 == 0 && c4 == 0) {
        // 정렬을 통해 위치 관계 파악 (p1 <= p2, p3 <= p4)
        if (p2 < p1) swap(p1, p2);
        if (p4 < p3) swap(p3, p4);

        // 겹치지 않는 경우
        if (p2 < p3 || p4 < p1) {
            cout << 0 << '\n';
        }
        // 한 점에서 만나는 경우 (끝점 접촉) -> 좌표 출력 필요
        else if (p2 == p3) {
            cout << 1 << '\n';
            cout << p2.x << " " << p2.y << '\n';
        }
        else if (p1 == p4) {
            cout << 1 << '\n';
            cout << p1.x << " " << p1.y << '\n';
        }
        // 선분으로 겹치는 경우 -> 좌표 출력 없음
        else {
            cout << 1 << '\n';
        }
    }
    // 2. 일반 교차 (또는 T자형 등으로 만나는 경우)
    else if (c1 * c2 <= 0 && c3 * c4 <= 0) {
        cout << 1 << '\n';
        
        // 교차점 계산 (Cramer's Rule)
        // __int128을 사용하여 중간 계산 오버플로우 방지
        ll x1 = p1.x, y1 = p1.y;
        ll x2 = p2.x, y2 = p2.y;
        ll x3 = p3.x, y3 = p3.y;
        ll x4 = p4.x, y4 = p4.y;

        // 분모: (x1-x2)(y3-y4) - (y1-y2)(x3-x4)
        long double det = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

        // 분자 계산 시 __int128 사용
        // 식: Px = [ (x1y2 - y1x2)(x3 - x4) - (x1 - x2)(x3y4 - y3x4) ] / det
        __int128 t1 = (__int128)x1 * y2 - (__int128)y1 * x2;
        __int128 t2 = (__int128)x3 * y4 - (__int128)y3 * x4;

        __int128 numX = t1 * (x3 - x4) - (x1 - x2) * t2;
        __int128 numY = t1 * (y3 - y4) - (y1 - y2) * t2;

        cout << fixed << setprecision(16) << (double)numX / det << " " << (double)numY / det << '\n';
    } 
    // 3. 만나지 않음
    else {
        cout << 0 << '\n';
    }

    return 0;
}
