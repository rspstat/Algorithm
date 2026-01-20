#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_NODES_LIMIT = 25000005; 

struct PersistentSegmentTree {
    int n, node_size = 1;
    vector<int> L, R, Val, Head;

    PersistentSegmentTree(int n) : n(n), L(MAX_NODES_LIMIT), R(MAX_NODES_LIMIT), Val(MAX_NODES_LIMIT), Head(n + 1) {}

    void update_head(int h_idx, int idx, int x) {
        if (Head[h_idx] == 0) {
            Head[h_idx] = node_size;
            node_size++;
        }
        Val[Head[h_idx]] += x;
        int cur = Head[h_idx], st = 1, en = n;
        while (st < en) {
            int mid = (st + en) / 2;
            if (idx <= mid) {
                if (L[cur] == 0) L[cur] = node_size++;
                cur = L[cur];
                Val[cur] += x;
                en = mid;
            } else {
                if (R[cur] == 0) R[cur] = node_size++;
                cur = R[cur];
                Val[cur] += x;
                st = mid + 1;
            }
        }
    }

    void update_from_ancestor(int anc_idx, int h_idx, int idx, int x) {
        Val[node_size] = Val[Head[anc_idx]] + x;
        L[node_size] = L[Head[anc_idx]];
        R[node_size] = R[Head[anc_idx]];
        Head[h_idx] = node_size;
        node_size++;

        int st = 1, en = n;
        int cur = Head[h_idx];
        
        while (st < en) {
            int mid = (st + en) / 2;
            if (idx <= mid) {
                Val[node_size] = Val[L[cur]] + x;
                L[node_size] = L[L[cur]];
                R[node_size] = R[L[cur]];
                L[cur] = node_size++;
                cur = L[cur];
                en = mid;
            } else {
                Val[node_size] = Val[R[cur]] + x;
                L[node_size] = L[R[cur]];
                R[node_size] = R[R[cur]];
                R[cur] = node_size++;
                cur = R[cur];
                st = mid + 1;
            }
        }
    }

    int query_range(int i, int j, int node, int nl, int nr) {
        if (j < nl || i > nr) return 0;
        if (i <= nl && nr <= j) return Val[node];
        int mid = (nl + nr) / 2;
        return query_range(i, j, L[node], nl, mid) + query_range(i, j, R[node], mid + 1, nr);
    }

    int query_count(int h_idx, int i, int j) {
        return query_range(i, j, Head[h_idx], 1, n);
    }

    int query_kth_recursive(int node, int cnt, int nl, int nr) {
        if (nl == nr) return nl;
        if (Val[L[node]] >= cnt) return query_kth_recursive(L[node], cnt, nl, (nl + nr) / 2);
        else return query_kth_recursive(R[node], cnt - Val[L[node]], (nl + nr) / 2 + 1, nr);
    }

    int query_kth(int h_idx, int cnt) {
        return query_kth_recursive(Head[h_idx], cnt, 1, n);
    }
};

int N, M, Q;
int Novel[100001];
ll Count[1000001];
ll PrefixSum[1000001];
bool IsFirstOccur[1000001];
bool IsProcessed[1000001];
bool IsStartPos[1000001];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> Q;

    stack<int> S;
    PersistentSegmentTree pst(1000001);

    for (int i = 0; i < N; i++) {
        cin >> Novel[i];
        if (!IsFirstOccur[Novel[i]]) {
            S.push(Novel[i]);
            IsFirstOccur[Novel[i]] = true;
            IsStartPos[i] = true;
        }
    }

    for (int i = 1; i <= M; i++) {
        pst.update_head(S.top(), i, 1);
    }

    for (int i = N - 1; i >= 1; i--) {
        if (IsStartPos[i]) {
            S.pop();
            pst.update_from_ancestor(Novel[i], S.top(), 1, 0);
            Count[Novel[i]] = pst.query_count(Novel[i], 1, M);
        }
        if (!IsProcessed[Novel[i]]) {
            pst.update_from_ancestor(S.top(), S.top(), Novel[i], -1);
            IsProcessed[Novel[i]] = true;
        }
    }

    Count[Novel[0]] = pst.query_count(Novel[0], 1, M);

    for (int i = 1; i <= M; i++) {
        if (!IsFirstOccur[i]) Count[i] = M;
        PrefixSum[i] = PrefixSum[i - 1] + Count[i];
    }

    while (Q--) {
        ll k;
        cin >> k;

        if (k > PrefixSum[M]) {
            cout << "-1 -1\n";
            continue;
        }

        int fst = 1;
        int fen = M;
        while (fst < fen) {
            int mid = (fst + fen) / 2;
            if (PrefixSum[mid] < k) fst = mid + 1;
            else fen = mid;
        }

        cout << fst << ' ';
        
        if (Count[fst] == M) {
            cout << k - PrefixSum[fst - 1] << '\n';
        } else {
            cout << pst.query_kth(fst, k - PrefixSum[fst - 1]) << '\n';
        }
    }
    
    return 0;
}
