#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 100001;
int arr[MAX];
vector<int> tree[MAX * 4];

void init(int node, int start, int end) {
    if (start == end) {
        tree[node].push_back(arr[start]);
        return;
    }
    
    int mid = (start + end) / 2;
    init(node * 2, start, mid);
    init(node * 2 + 1, mid + 1, end);
    
    vector<int>& left = tree[node * 2];
    vector<int>& right = tree[node * 2 + 1];
    
    tree[node].resize(left.size() + right.size());
    merge(left.begin(), left.end(), right.begin(), right.end(), tree[node].begin());
}

int query(int node, int start, int end, int left, int right, int k) {
    if (left > end || right < start) return 0;
    
    if (left <= start && end <= right) {
        return tree[node].end() - upper_bound(tree[node].begin(), tree[node].end(), k);
    }
    
    int mid = (start + end) / 2;
    return query(node * 2, start, mid, left, right, k) + query(node * 2 + 1, mid + 1, end, left, right, k);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
    }
    
    init(1, 1, n);
    
    int m;
    cin >> m;
    
    int last_ans = 0;
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        
        int i = a ^ last_ans;
        int j = b ^ last_ans;
        int k = c ^ last_ans;
        
        last_ans = query(1, 1, n, i, j, k);
        cout << last_ans << "\n";
    }
    
    return 0;
}
