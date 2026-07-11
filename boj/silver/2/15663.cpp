#include <bits/stdc++.h>
using namespace std;

int n, m;

void solve() {
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a.begin(), a.end());

    vector<int> used(n, 0), seq;
    ostringstream out;

    function<void(int)> dfs = [&](int depth) {
        if (depth == m) {
            for (int i = 0; i < m; ++i) {
                if (i) out << ' ';
                out << seq[i];
            }
            out << '\n';
            return;
        }
        int prev = INT_MIN; // 같은 깊이에서 중복 값 방지
        for (int i = 0; i < n; ++i) {
            if (used[i]) continue;
            if (a[i] == prev) continue; // 이 깊이에서 이미 쓴 값이면 스킵
            used[i] = 1;
            seq.push_back(a[i]);
            prev = a[i];
            dfs(depth + 1);
            seq.pop_back();
            used[i] = 0;
        }
    };

    dfs(0);
    cout << out.str();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
