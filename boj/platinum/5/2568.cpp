#include <bits/stdc++.h>
using namespace std;

int n;

void solve() {
    cin >> n;
    vector<pair<int,int>> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i].first >> a[i].second;
    sort(a.begin(), a.end()); // A 기준 정렬

    vector<int> tails;              // LIS 끝값들 (B 기준)
    vector<int> tails_idx;          // 각 길이의 마지막 원소의 인덱스
    vector<int> prev_idx(n, -1);    // LIS 복원용 이전 인덱스

    for (int i = 0; i < n; ++i) {
        int b = a[i].second;
        int pos = lower_bound(tails.begin(), tails.end(), b) - tails.begin();
        if (pos == (int)tails.size()) {
            tails.push_back(b);
            tails_idx.push_back(i);
        } else {
            tails[pos] = b;
            tails_idx[pos] = i;
        }
        if (pos > 0) prev_idx[i] = tails_idx[pos - 1];
    }

    // LIS 구성 요소 인덱스 복원
    int len = (int)tails.size();
    int idx = tails_idx.back();
    vector<int> lis_idx;
    while (idx != -1) {
        lis_idx.push_back(idx);
        idx = prev_idx[idx];
    }
    reverse(lis_idx.begin(), lis_idx.end());

    // LIS에 속하는 A를 표시
    vector<char> in_lis(n, 0);
    for (int id : lis_idx) in_lis[id] = 1;

    // 제거해야 할 전깃줄 A들(오름차순: 이미 A로 정렬되어 있으므로 순서대로 출력)
    vector<int> removeA;
    for (int i = 0; i < n; ++i) if (!in_lis[i]) removeA.push_back(a[i].first);

    cout << n - len << '\n';
    for (int x : removeA) cout << x << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
