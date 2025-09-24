#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int N, M, K;
vector<ll> arr;
vector<ll> tree;

ll sum(int idx) {
    ll result = 0;
    while (idx > 0) {
        result += tree[idx];
        idx -= (idx & -idx);
    }
    return result;
}

void update(int idx, ll diff) {
    while (idx <= N) {
        tree[idx] += diff;
        idx += (idx & -idx);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> K;
    arr.resize(N + 1);
    tree.resize(N + 1, 0);

    for (int i = 1; i <= N; ++i) {
        cin >> arr[i];
        update(i, arr[i]);
    }

    int total_queries = M + K;
    while (total_queries--) {
        int a;
        ll b, c;
        cin >> a >> b >> c;

        if (a == 1) {
            ll diff = c - arr[b];
            arr[b] = c;
            update(b, diff);
        } else {
            cout << sum(c) - sum(b - 1) << "\n";
        }
    }

    return 0;
}
