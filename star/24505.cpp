#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;
const int MAX = 100005;

long long bit[12][MAX];
int N;

void update(int k, int idx, long long val) {
    while (idx <= N) {
        bit[k][idx] = (bit[k][idx] + val) % MOD;
        idx += (idx & -idx);
    }
}

long long query(int k, int idx) {
    long long res = 0;
    while (idx > 0) {
        res = (res + bit[k][idx]) % MOD;
        idx -= (idx & -idx);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;

        update(1, x, 1);

        for (int k = 2; k <= 11; k++) {
            long long prev_ways = query(k - 1, x - 1);
            update(k, x, prev_ways);
        }
    }

    cout << query(11, N) << "\n";

    return 0;
}
