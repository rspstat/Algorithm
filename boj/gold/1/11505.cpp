#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
const int MOD = 1000000007;

int N, M, K;
vector<ll> arr, tree;

ll init(int node, int start, int end) {
    if (start == end) {
        return tree[node] = arr[start];
    }
    int mid = (start + end) / 2;
    ll left_product = init(node * 2, start, mid);
    ll right_product = init(node * 2 + 1, mid + 1, end);
    return tree[node] = (left_product * right_product) % MOD;
}

ll update(int node, int start, int end, int index, ll val) {
    if (index < start || index > end) {
        return tree[node];
    }
    if (start == end) {
        return tree[node] = val;
    }
    int mid = (start + end) / 2;
    ll left_product = update(node * 2, start, mid, index, val);
    ll right_product = update(node * 2 + 1, mid + 1, end, index, val);
    return tree[node] = (left_product * right_product) % MOD;
}

ll query(int node, int start, int end, int left, int right) {
    if (right < start || left > end) {
        return 1;
    }
    if (left <= start && end <= right) {
        return tree[node];
    }
    int mid = (start + end) / 2;
    ll left_product = query(node * 2, start, mid, left, right);
    ll right_product = query(node * 2 + 1, mid + 1, end, left, right);
    return (left_product * right_product) % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> K;
    arr.resize(N + 1);
    tree.resize(N * 4);

    for (int i = 1; i <= N; ++i) {
        cin >> arr[i];
    }

    init(1, 1, N);

    int total_queries = M + K;
    while (total_queries--) {
        int type, b;
        ll c;
        cin >> type >> b >> c;
        if (type == 1) {
            update(1, 1, N, b, c);
            arr[b] = c;
        } else {
            cout << query(1, 1, N, b, (int)c) << "\n";
        }
    }

    return 0;
}
