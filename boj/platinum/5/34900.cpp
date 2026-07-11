#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p;
    vector<int> sz;

    DSU(int n) : p(n + 1), sz(n + 1, 1) {
        for (int i = 1; i <= n; i++) p[i] = i;
    }

    int find(int x) {
        while (p[x] != x) {
            p[x] = p[p[x]];
            x = p[x];
        }
        return x;
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
        return true;
    }

    int size(int x) {
        return sz[find(x)];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<int> a(N + 1);
    long long ones = 0;
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
        ones += a[i];
    }

    if (a[N] != 0) {
        cout << "No\n";
        return 0;
    }

    if (ones != M) {
        cout << "No\n";
        return 0;
    }

    DSU dsu(N);
    bool hasCycle = false;

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        if (!dsu.unite(u, v)) hasCycle = true;
    }

    if (hasCycle) {
        cout << "No\n";
        return 0;
    }

    // collect component sizes
    vector<int> compSizes;
    compSizes.reserve(N);

    vector<int> seen(N + 1, 0);
    for (int i = 1; i <= N; i++) {
        int r = dsu.find(i);
        if (seen[r]) continue;
        seen[r] = 1;
        compSizes.push_back(dsu.sz[r]);
    }

    int C = (int)compSizes.size();
    int zeros = N - (int)ones;

    if (zeros != C) {
        cout << "No\n";
        return 0;
    }

    sort(compSizes.begin(), compSizes.end(), greater<int>());

    long long cap = 0;
    int idx = 0;

    for (int x = N; x >= 1; x--) {
        if (a[x] == 0) {
            // start a new component (use the largest remaining one)
            int s = compSizes[idx++];
            cap += (long long)(s - 1);
        } else {
            // need to attach one vertex into some already-started component
            if (cap == 0) {
                cout << "No\n";
                return 0;
            }
            cap--;
        }
    }

    cout << "Yes\n";
    return 0;
}
