#include <bits/stdc++.h>
using namespace std;

vector<int> in, post, pre;
unordered_map<int, int> pos;

void solve(int il, int ir, int pl, int pr) {
    if (il > ir) return;
    
    int root = post[pr];
    pre.push_back(root);
    
    if (il == ir) return;
    
    int idx = pos[root];
    int left_size = idx - il;
    
    solve(il, idx - 1, pl, pl + left_size - 1);
    solve(idx + 1, ir, pl + left_size, pr - 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    in.resize(n);
    post.resize(n);
    
    for (int i = 0; i < n; i++) {
        cin >> in[i];
        pos[in[i]] = i;
    }
    
    for (int i = 0; i < n; i++) {
        cin >> post[i];
    }
    
    solve(0, n - 1, 0, n - 1);
    
    for (int x : pre) {
        cout << x << ' ';
    }
    cout << '\n';
    
    return 0;
}
