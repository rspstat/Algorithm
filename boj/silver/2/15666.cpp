#include <bits/stdc++.h>
using namespace std;

int n, m;

void solve() {
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end()); // 입력 중복 제거

    vector<int> seq;
    ostringstream out;

    function<void(int,int)> dfs = [&](int depth, int start) {
        if (depth == m) {
            for (int i = 0; i < m; ++i) {
                if (i) out << ' ';
                out << seq[i];
            }
            out << '\n';
            return;
        }
        for (int i = start; i < (int)a.size(); ++i) {
            seq.push_back(a[i]);
            dfs(depth + 1, i); // 같은 수를 다시 사용할 수 있음 (비내림차순)
            seq.pop_back();
        }
    };

    dfs(0, 0);
    cout << out.str();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
