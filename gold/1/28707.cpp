#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct VecHash {
    size_t operator()(const vector<int>& v) const noexcept {
        size_t h = 1469598103934665603ULL; // FNV offset
        for (int x : v) {
            h ^= (size_t)(x + 0x9e3779b9);
            h *= 1099511628211ULL;          // FNV prime
        }
        return h;
    }
};

inline bool is_sorted_nondec(const vector<int>& a) {
    for (int i = 1; i < (int)a.size(); ++i)
        if (a[i-1] > a[i]) return false;
    return true;
}

void solve() {
    int n; 
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    int m; 
    cin >> m;
    struct Op { int u, v, c; };
    vector<Op> ops(m);
    for (int i = 0; i < m; ++i) {
        int l, r, c; 
        cin >> l >> r >> c;
        --l; --r;
        ops[i] = {l, r, c};
    }

    // 값 압축: 동일 값 -> 동일 랭크 (중복값 안전)
    vector<int> uniq = a;
    sort(uniq.begin(), uniq.end());
    uniq.erase(unique(uniq.begin(), uniq.end()), uniq.end());

    vector<int> start(n);
    for (int i = 0; i < n; ++i) {
        start[i] = int(lower_bound(uniq.begin(), uniq.end(), a[i]) - uniq.begin());
    }

    if (is_sorted_nondec(start)) { 
        cout << 0 << '\n'; 
        return; 
    }

    // 다익스트라 (상태: 랭크 배열)
    unordered_map<vector<int>, ll, VecHash> dist;
    dist.reserve(50000);
    dist[start] = 0;

    using Node = pair<ll, vector<int>>;
    struct Cmp { bool operator()(const Node& A, const Node& B) const { return A.first > B.first; } };
    priority_queue<Node, vector<Node>, Cmp> pq;
    pq.push({0, start});

    vector<int> cur, nxt;
    while (!pq.empty()) {
        auto [d, s] = pq.top(); pq.pop();
        auto it = dist.find(s);
        if (it != dist.end() && d > it->second) continue;

        if (is_sorted_nondec(s)) {
            cout << d << '\n';
            return;
        }

        cur = s;
        for (const auto& op : ops) {
            nxt = cur;
            swap(nxt[op.u], nxt[op.v]);
            ll nd = d + op.c;
            auto jt = dist.find(nxt);
            if (jt == dist.end() || nd < jt->second) {
                dist[nxt] = nd;
                pq.push({nd, nxt});
            }
        }
    }

    // 비내림차순 정렬이 불가능한 경우
    cout << -1 << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
