#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int MAX = 30005;

struct Query {
    string type;
    int a, b;
};

int n, q;
int penguins[MAX];
vector<int> adj[MAX];
vector<Query> queries;

// HLD 관련 변수
int parent[MAX], depth[MAX], heavy[MAX], head[MAX], pos[MAX];
int sz[MAX];
int cur_pos;

// 세그먼트 트리
int seg[MAX * 4];

// Union-Find 구조체
struct UF {
    int p[MAX];
    void init() {
        for (int i = 1; i <= n; i++) p[i] = i;
    }
    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        p[b] = a;
        return true;
    }
} uf_offline, uf_online;

// 1. DFS for Subtree Size & Heavy Child
void dfs_sz(int u, int p, int d) {
    sz[u] = 1;
    parent[u] = p;
    depth[u] = d;
    int max_sz = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs_sz(v, u, d + 1);
        sz[u] += sz[v];
        if (sz[v] > max_sz) {
            max_sz = sz[v];
            heavy[u] = v;
        }
    }
}

// 2. DFS for HLD Decomposition
void dfs_hld(int u, int h) {
    head[u] = h;
    pos[u] = ++cur_pos;
    if (heavy[u]) dfs_hld(heavy[u], h);
    for (int v : adj[u]) {
        if (v != parent[u] && v != heavy[u]) {
            dfs_hld(v, v);
        }
    }
}

// Segment Tree Update
void update(int node, int start, int end, int idx, int val) {
    if (idx < start || idx > end) return;
    if (start == end) {
        seg[node] = val;
        return;
    }
    int mid = (start + end) / 2;
    update(node * 2, start, mid, idx, val);
    update(node * 2 + 1, mid + 1, end, idx, val);
    seg[node] = seg[node * 2] + seg[node * 2 + 1];
}

// Segment Tree Query
int query_seg(int node, int start, int end, int left, int right) {
    if (left > end || right < start) return 0;
    if (left <= start && end <= right) return seg[node];
    int mid = (start + end) / 2;
    return query_seg(node * 2, start, mid, left, right) + query_seg(node * 2 + 1, mid + 1, end, left, right);
}

// HLD Path Query
int query_path(int u, int v) {
    int res = 0;
    while (head[u] != head[v]) {
        if (depth[head[u]] < depth[head[v]]) swap(u, v);
        res += query_seg(1, 1, n, pos[head[u]], pos[u]);
        u = parent[head[u]];
    }
    if (depth[u] > depth[v]) swap(u, v);
    res += query_seg(1, 1, n, pos[u], pos[v]);
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> penguins[i];

    cin >> q;
    for (int i = 0; i < q; i++) {
        string t; int a, b;
        cin >> t >> a >> b;
        queries.push_back({t, a, b});
    }

    // Step 1: 오프라인으로 최종 그래프 구성
    uf_offline.init();
    for (auto& qry : queries) {
        if (qry.type == "bridge") {
            if (uf_offline.unite(qry.a, qry.b)) {
                adj[qry.a].push_back(qry.b);
                adj[qry.b].push_back(qry.a);
            }
        }
    }

    // Step 2: HLD 구성 (Forest일 수 있으므로 모든 노드 확인)
    for (int i = 1; i <= n; i++) {
        if (!sz[i]) {
            dfs_sz(i, 0, 1);
            dfs_hld(i, i);
        }
    }

    // Step 3: 초기 펭귄 수 세그먼트 트리에 업데이트
    for (int i = 1; i <= n; i++) {
        update(1, 1, n, pos[i], penguins[i]);
    }

    // Step 4: 쿼리 처리
    uf_online.init();
    for (auto& qry : queries) {
        if (qry.type == "bridge") {
            if (uf_online.unite(qry.a, qry.b)) {
                cout << "yes\n";
            } else {
                cout << "no\n";
            }
        } else if (qry.type == "penguins") {
            update(1, 1, n, pos[qry.a], qry.b);
            penguins[qry.a] = qry.b;
        } else if (qry.type == "excursion") {
            if (uf_online.find(qry.a) != uf_online.find(qry.b)) {
                cout << "impossible\n";
            } else {
                cout << query_path(qry.a, qry.b) << '\n';
            }
        }
    }

    return 0;
}
