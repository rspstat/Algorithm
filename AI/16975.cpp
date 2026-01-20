#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int N, M;
ll tree[100005];
ll A[100005];

// 펜윅 트리 업데이트: idx 위치에 val을 더함
void update(int idx, ll val) {
    while (idx <= N) {
        tree[idx] += val;
        idx += (idx & -idx);
    }
}

// 펜윅 트리 쿼리: 1부터 idx까지의 합을 반환
ll query(int idx) {
    ll res = 0;
    while (idx > 0) {
        res += tree[idx];
        idx -= (idx & -idx);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
        // 초기 차분 배열을 트리 구성에 반영
        update(i, A[i] - A[i - 1]);
    }

    cin >> M;
    while (M--) {
        int type;
        cin >> type;
        if (type == 1) {
            int i, j;
            ll k;
            cin >> i >> j >> k;
            // 구간 [i, j]에 k를 더하는 연산
            update(i, k);
            update(j + 1, -k);
        } else {
            int x;
            cin >> x;
            // Point Query: A[x]의 현재 값 출력
            cout << query(x) << "\n";
        }
    }

    return 0;
}
