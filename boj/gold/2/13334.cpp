#include <bits/stdc++.h>
using namespace std;

struct Seg {
    int s, e;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Seg> v(n);

    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        if (a > b) swap(a, b);
        v[i] = {a, b};
    }

    int d;
    cin >> d;

    sort(v.begin(), v.end(), [](const Seg& x, const Seg& y) {
        return x.e < y.e;
    });

    priority_queue<int, vector<int>, greater<int>> pq;
    int ans = 0;

    for (auto& seg : v) {
        if (seg.e - seg.s > d) continue;
        pq.push(seg.s);
        while (!pq.empty() && pq.top() < seg.e - d) pq.pop();
        ans = max(ans, (int)pq.size());
    }

    cout << ans << "\n";
    return 0;
}
