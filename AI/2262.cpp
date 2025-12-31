#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Pt {
    int x, y;
};

int n;
vector<Pt> p;

// 거리 제곱 반환
int dist(Pt a, Pt b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool cmpY(const Pt& a, const Pt& b) {
    return a.y < b.y;
}

int solve(int l, int r) {
    if (l == r) return 2e9;
    if (r - l == 1) return dist(p[l], p[r]);

    int mid = (l + r) / 2;
    int cur = min(solve(l, mid), solve(mid + 1, r));

    vector<Pt> v;
    int mid_x = p[mid].x;
    
    // 중간 라인 기준 x거리 제곱이 cur 미만인 점만 후보군
    for (int i = l; i <= r; i++) {
        int dx = p[i].x - mid_x;
        if (dx * dx < cur) {
            v.push_back(p[i]);
        }
    }

    // y좌표 기준 정렬하여 비교 횟수 줄이기 (Sweep Line 아이디어)
    sort(v.begin(), v.end(), cmpY);

    int sz = v.size();
    for (int i = 0; i < sz; i++) {
        for (int j = i + 1; j < sz; j++) {
            int dy = v[j].y - v[i].y;
            // y 차이가 이미 최소 거리보다 크면 더 볼 필요 없음
            if (dy * dy >= cur) break;
            cur = min(cur, dist(v[i], v[j]));
        }
    }

    return cur;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    p.resize(n);
    for (int i = 0; i < n; i++) cin >> p[i].x >> p[i].y;

    sort(p.begin(), p.end(), [](const Pt& a, const Pt& b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });

    cout << solve(0, n - 1);

    return 0;
}
