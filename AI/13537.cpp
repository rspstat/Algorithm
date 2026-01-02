#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 100005;
int n, m;
int a[MAX];
vector<int> tree[MAX * 4];

// 머지 소트 트리 빌드 (O(N log N))
void build(int node, int s, int e) {
    if (s == e) {
        tree[node].push_back(a[s]);
        return;
    }
    int mid = (s + e) / 2;
    build(node * 2, s, mid);
    build(node * 2 + 1, mid + 1, e);
    
    // 두 자식 노드의 정렬된 벡터를 병합
    tree[node].resize(tree[node * 2].size() + tree[node * 2 + 1].size());
    merge(tree[node * 2].begin(), tree[node * 2].end(),
          tree[node * 2 + 1].begin(), tree[node * 2 + 1].end(),
          tree[node].begin());
}

// 쿼리 처리 (O(log^2 N))
int qry(int node, int s, int e, int l, int r, int k) {
    if (l > e || r < s) return 0;
    if (l <= s && e <= r) {
        // 구간 내에서 k보다 큰 원소의 개수 (upper_bound)
        return tree[node].end() - upper_bound(tree[node].begin(), tree[node].end(), k);
    }
    int mid = (s + e) / 2;
    return qry(node * 2, s, mid, l, r, k) + qry(node * 2 + 1, mid + 1, e, l, r, k);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    build(1, 1, n);

    cin >> m;
    while (m--) {
        int i, j, k;
        cin >> i >> j >> k;
        cout << qry(1, 1, n, i, j, k) << '\n';
    }

    return 0;
}
