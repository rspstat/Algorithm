#include <bits/stdc++.h>
using namespace std;

int N, ans = 0;

vector<int> pack(const vector<int> &v, bool rev) {
    vector<int> a = v;
    if (rev) reverse(a.begin(), a.end());

    vector<int> nz;
    nz.reserve(a.size());
    for (int x : a) if (x) nz.push_back(x);

    vector<int> out;
    out.reserve(a.size());

    for (size_t i = 0; i < nz.size(); ) {
        if (i + 1 < nz.size() && nz[i] == nz[i + 1]) {
            out.push_back(nz[i] * 2);
            i += 2;
        } else {
            out.push_back(nz[i]);
            i += 1;
        }
    }
    while (out.size() < a.size()) out.push_back(0);

    if (rev) reverse(out.begin(), out.end());
    return out;
}

vector<vector<int>> moveBoard(const vector<vector<int>> &b, int dir) {
    vector<vector<int>> nb = b;

    if (dir == 0) { // up
        for (int c = 0; c < N; ++c) {
            vector<int> col(N);
            for (int r = 0; r < N; ++r) col[r] = b[r][c];
            vector<int> m = pack(col, false);
            for (int r = 0; r < N; ++r) nb[r][c] = m[r];
        }
    } else if (dir == 1) { // down
        for (int c = 0; c < N; ++c) {
            vector<int> col(N);
            for (int r = 0; r < N; ++r) col[r] = b[r][c];
            vector<int> m = pack(col, true);
            for (int r = 0; r < N; ++r) nb[r][c] = m[r];
        }
    } else if (dir == 2) { // left
        for (int r = 0; r < N; ++r) {
            vector<int> m = pack(b[r], false);
            nb[r] = m;
        }
    } else { // right
        for (int r = 0; r < N; ++r) {
            vector<int> m = pack(b[r], true);
            nb[r] = m;
        }
    }
    return nb;
}

int maxTile(const vector<vector<int>> &b) {
    int m = 0;
    for (auto &row : b) for (int x : row) m = max(m, x);
    return m;
}

void dfs(const vector<vector<int>> &b, int d) {
    ans = max(ans, maxTile(b));
    if (d == 5) return;

    for (int k = 0; k < 4; ++k) {
        auto nb = moveBoard(b, k);
        if (nb == b) continue;              // 변화 없으면 가지치기
        dfs(nb, d + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    vector<vector<int>> b(N, vector<int>(N));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> b[i][j];

    dfs(b, 0);
    cout << ans << '\n';
    return 0;
}
