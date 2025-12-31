#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

struct Rect {
    ll w, h;
};

struct Line {
    ll m, k;
    ll eval(ll x) { return m * x + k; }
};

int n;
vector<Rect> a, clean;
vector<Line> hull;
int ptr = 0;

// 두 직선의 교점 (x좌표) 계산. 
// m1 > m2인 상태로 들어옴 (기울기 감소 순서)
double intersect(Line& l1, Line& l2) {
    return (double)(l2.k - l1.k) / (l1.m - l2.m);
}

void add_line(ll m, ll k) {
    Line new_line = {m, k};
    while (hull.size() >= 2) {
        // 교차점 비교: 기존 마지막 직선이 더 빨리 쓸모없어지면 제거
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
    a.resize(n);
    for (int i = 0; i < n; i++) cin >> a[i].w >> a[i].h;

    // 1. w 오름차순, w 같으면 h 오름차순 정렬
    sort(a.begin(), a.end(), [](const Rect& u, const Rect& v) {
        if (u.w != v.w) return u.w < v.w;
        return u.h < v.h;
    });

    // 2. 불필요한 땅 제거 (스택 활용)
    // 현재 땅보다 w도 크고 h도 큰 땅이 뒤에 있으면 현재 땅은 무시해도 됨
    // 정렬했으므로 뒤에 오는 땅은 무조건 w가 크거나 같음. h만 비교하면 됨.
    for (auto& r : a) {
        while (!clean.empty() && clean.back().h <= r.h) {
            clean.pop_back();
        }
        clean.push_back(r);
    }

    // DP 수행
    // DP[i] = min(DP[j] + clean[i].w * clean[j+1].h)
    // 직선: 기울기 clean[j+1].h, 절편 DP[j]
    
    // 초기값: DP[0] = 0에서 시작하는 직선 (첫 그룹을 0~i까지 묶는 경우)
    add_line(clean[0].h, 0);

    ll dp = 0;
    int m = clean.size();
    
    for (int i = 0; i < m; i++) {
        ll x = clean[i].w;

        // 쿼리 x가 증가하므로 포인터 이동 (CHT 최적화)
        while (ptr + 1 < hull.size() && hull[ptr].eval(x) >= hull[ptr + 1].eval(x)) {
            ptr++;
        }

        dp = hull[ptr].eval(x);

        // 다음 턴을 위한 직선 추가
        // i번째까지 처리했으므로, 다음 그룹의 시작 높이는 clean[i+1].h, 절편은 현재 dp
        if (i < m - 1) {
            add_line(clean[i + 1].h, dp);
        }
    }

    cout << dp;

    return 0;
}
