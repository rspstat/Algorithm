#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int SZ = 1000005;
int n, q_cnt;
int a[SZ], bit[SZ], lst[SZ], ans[SZ];
vector<pair<int, int>> qs[SZ];
vector<int> v;

// 펜윅 트리 업데이트
void u(int i, int val) {
    while (i <= n) {
        bit[i] += val;
        i += i & -i;
    }
}

// 펜윅 트리 쿼리
int qry(int i) {
    int ret = 0;
    while (i) {
        ret += bit[i];
        i -= i & -i;
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        v.push_back(a[i]);
    }

    // 좌표 압축 (값의 범위가 클 수 있으므로 1~N 범위로 매핑)
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
    }

    cin >> q_cnt;
    for (int i = 0; i < q_cnt; i++) {
        int l, r;
        cin >> l >> r;
        qs[r].push_back({l, i});
    }

    // Sweeping: 오른쪽으로 이동하며 가장 최근 위치만 1로 유지
    for (int i = 1; i <= n; i++) {
        if (lst[a[i]]) u(lst[a[i]], -1); // 이전에 등장했던 위치 제거
        u(i, 1);                         // 현재 위치 추가
        lst[a[i]] = i;

        // 현재 위치(i)가 쿼리의 끝점(r)인 경우 답 계산
        for (auto& p : qs[i]) {
            ans[p.second] = qry(i) - qry(p.first - 1);
        }
    }

    for (int i = 0; i < q_cnt; i++) cout << ans[i] << '\n';

    return 0;
}
