#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int n, m, k, res;
int a[100005], cnt[1000005], ans[100005];

struct Q {
    int l, r, idx;
    // 힐베르트 곡선 순서 또는 지그재그 정렬 최적화
    bool operator<(const Q& o) const {
        if (l / k != o.l / k) return l / k < o.l / k;
        return (l / k) & 1 ? r < o.r : r > o.r;
    }
};

void add(int x) {
    if (cnt[x]++ == 0) res++;
}

void del(int x) {
    if (--cnt[x] == 0) res--;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    k = sqrt(n);
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
        ans[q[i].idx] = res;
    }

    for (int i = 0; i < m; i++) cout << ans[i] << '\n';

    return 0;
}
