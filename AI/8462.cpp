#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long ll;

int n, t, k;
int a[100005];
int cnt[1000005]; // 값의 범위: 1 ~ 1,000,000
ll cur = 0;
ll ans[100005];

struct Q {
    int l, r, idx;
    bool operator<(const Q& o) const {
        if (l / k != o.l / k) return l / k < o.l / k;
        return (l / k) & 1 ? r < o.r : r > o.r;
    }
};

void add(int x) {
    cur -= (ll)x * cnt[x] * cnt[x];
    cnt[x]++;
    cur += (ll)x * cnt[x] * cnt[x];
}

void del(int x) {
    cur -= (ll)x * cnt[x] * cnt[x];
    cnt[x]--;
    cur += (ll)x * cnt[x] * cnt[x];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> t;
    k = sqrt(n);

    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<Q> qs(t);
    for (int i = 0; i < t; i++) {
        cin >> qs[i].l >> qs[i].r;
        qs[i].idx = i;
    }

    sort(qs.begin(), qs.end());

    int l = 1, r = 0;
    for (int i = 0; i < t; i++) {
        while (l > qs[i].l) add(a[--l]);
        while (r < qs[i].r) add(a[++r]);
        while (l < qs[i].l) del(a[l++]);
        while (r > qs[i].r) del(a[r--]);
        ans[qs[i].idx] = cur;
    }

    for (int i = 0; i < t; i++) cout << ans[i] << '\n';

    return 0;
}
