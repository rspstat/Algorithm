#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int N, M, K;
vector<ll> arr;
vector<ll> tree;
vector<ll> lazy;

// 세그먼트 트리 초기화
ll init(int node, int start, int end) {
    if (start == end) {
        return tree[node] = arr[start];
    }
    int mid = (start + end) / 2;
    return tree[node] = init(node * 2, start, mid) + init(node * 2 + 1, mid + 1, end);
}

// 레이지 값 전파
void update_lazy(int node, int start, int end) {
    if (lazy[node] != 0) {
        tree[node] += (end - start + 1) * lazy[node];
        if (start != end) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

// 구간 업데이트
void update_range(int node, int start, int end, int left, int right, ll diff) {
    update_lazy(node, start, end);

    if (left > end || right < start) return;

    if (left <= start && end <= right) {
        tree[node] += (end - start + 1) * diff;
        if (start != end) {
            lazy[node * 2] += diff;
            lazy[node * 2 + 1] += diff;
        }
        return;
    }

    int mid = (start + end) / 2;
    update_range(node * 2, start, mid, left, right, diff);
    update_range(node * 2 + 1, mid + 1, end, left, right, diff);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

// 구간 합 쿼리
ll query(int node, int start, int end, int left, int right) {
    update_lazy(node, start, end);

    if (left > end || right < start) return 0;
    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) / 2;
    return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> K;

    arr.resize(N + 1);
    tree.resize(N * 4);
    lazy.resize(N * 4);

    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
    }

    init(1, 1, N);

    for (int i = 0; i < M + K; i++) {
        int a;
        cin >> a;
        if (a == 1) {
            int b, c;
            ll d;
            cin >> b >> c >> d;
            update_range(1, 1, N, b, c, d);
        } else {
            int b, c;
            cin >> b >> c;
            cout << query(1, 1, N, b, c) << "\n";
        }
    }

    return 0;
}
