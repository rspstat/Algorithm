#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9 + 7;

int N, M;
vector<int> arr;
vector<pair<int, int>> tree;

pair<int, int> init(int node, int start, int end) {
    if (start == end) {
        return tree[node] = {arr[start], arr[start]};
    }

    int mid = (start + end) / 2;
    pair<int, int> left_res = init(node * 2, start, mid);
    pair<int, int> right_res = init(node * 2 + 1, mid + 1, end);

    int min_val = min(left_res.first, right_res.first);
    int max_val = max(left_res.second, right_res.second);

    return tree[node] = {min_val, max_val};
}

pair<int, int> query(int node, int start, int end, int left, int right) {
    if (right < start || left > end) {
        return {INF, 0};
    }

    if (left <= start && end <= right) {
        return tree[node];
    }

    int mid = (start + end) / 2;
    pair<int, int> left_res = query(node * 2, start, mid, left, right);
    pair<int, int> right_res = query(node * 2 + 1, mid + 1, end, left, right);

    int min_val = min(left_res.first, right_res.first);
    int max_val = max(left_res.second, right_res.second);

    return {min_val, max_val};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    arr.resize(N + 1);
    tree.resize(N * 4);

    for (int i = 1; i <= N; ++i) {
        cin >> arr[i];
    }

    init(1, 1, N);

    while (M--) {
        int a, b;
        cin >> a >> b;
        pair<int, int> result = query(1, 1, N, a, b);
        cout << result.first << " " << result.second << "\n";
    }

    return 0;
}
