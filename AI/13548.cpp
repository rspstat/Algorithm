#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int n, m, sz;
int a[100001];
int cnt[100001]; // cnt[v]: 값 v의 등장 횟수
int cc[100001];  // cc[f]: 등장 횟수가 f인 값의 개수
int ans[100001];
int mx = 0;

struct Q {
    int l, r, idx;
    bool operator<(const Q& o) const {
        if (l / sz != o.l / sz) return l / sz < o.l / sz;
        return (l / sz) & 1 ? r < o.r : r > o.r;
    }
};

void add(int x) {
    if (cnt[x] != 0) cc[cnt[x]]--;
    cnt[x]++;
    cc[cnt[x]]++;
    if (mx < cnt[x]) mx = cnt[x];
}

void del(int x) {
    cc[cnt[x]]--;
    // 현재 최빈값 개수를 가진 유일한 숫자가 빠지는 경우 mx 감소
    if (cnt[x] == mx && cc[cnt[x]] == 0) mx--;
    cnt[x]--;
    if (cnt[x] != 0) cc[cnt[x]]++;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    sz = sqrt(n);
    for (int i = 1; i <= n; i++) cin >> a[i];

    cin >> m;
    vector<Q> q(m);
    for (int i = 0; i < m; i++) {
        cin >> q[i].l >> q[i].r;
        q[i].idx = i;
    }

    sort(q.begin(), q.end());

    int l = 1, r = 0;
    for (int i = 0; i < m; i++) {
        while (l > q[i].l) add(a[--l]);
        while (r < q[i].r) add(a[++r]);
        while (l < q[i].l) del(a[l++]);
        while (r > q[i].r) del(a[r--]);
        ans[q[i].idx] = mx;
    }

    for (int i = 0; i < m; i++) cout << ans[i] << '\n';

    return 0;
}
