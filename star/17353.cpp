#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int n, q;
ll a[100005];
ll bit_cnt[100005]; // x의 계수 관리 (기울기)
ll bit_val[100005]; // 상수항 관리

// 펜윅 트리 업데이트 (Point Update)
void upd(ll* bit, int idx, ll val) {
    while (idx <= n) {
        bit[idx] += val;
        idx += idx & -idx;
    }
}

// 펜윅 트리 구간 업데이트 (Range Update -> Difference Array 활용)
void range_upd(ll* bit, int l, int r, ll val) {
    upd(bit, l, val);
    upd(bit, r + 1, -val);
}

// 펜윅 트리 쿼리 (Prefix Sum -> Point Value)
ll qry(ll* bit, int idx) {
    ll ret = 0;
    while (idx > 0) {
        ret += bit[idx];
        idx -= idx & -idx;
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    cin >> q;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r;
            cin >> l >> r;
            // 값 증가량: (i - L + 1) = 1 * i + (1 - L)
            // 계수 부분(+1)과 상수 부분(1-L)을 나누어 업데이트
            range_upd(bit_cnt, l, r, 1);
            range_upd(bit_val, l, r, -(l - 1));
        } else {
            int x;
            cin >> x;
            ll cnt = qry(bit_cnt, x);
            ll val = qry(bit_val, x);
            // 최종 값 = 초기값 + (기울기 * x) + 상수
            cout << a[x] + cnt * x + val << '\n';
        }
    }

    return 0;
}
