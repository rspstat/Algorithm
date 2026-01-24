#include <bits/stdc++.h>
using namespace std;

static const int INF = 1e9;
static const int V = 3000;

struct Node {
    int val, pos;
};

static inline Node betterNode(const Node& a, const Node& b) {
    if (a.val != b.val) return (a.val < b.val) ? a : b;
    return (a.pos < b.pos) ? a : b;
}

struct SparseMin {
    int n;
    vector<int> lg;
    vector<vector<Node>> st;

    void build(const vector<int>& arr) {
        n = (int)arr.size() - 1;
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
        int K = lg[n] + 1;
        st.assign(K, vector<Node>(n + 1));

        for (int i = 1; i <= n; i++) st[0][i] = {arr[i], i};

        for (int k = 1; k < K; k++) {
            int len = 1 << k;
            int half = len >> 1;
            for (int i = 1; i + len - 1 <= n; i++) {
                st[k][i] = betterNode(st[k - 1][i], st[k - 1][i + half]);
            }
        }
    }

    int queryMin(int l, int r) const {
        if (l > r) return INF;
        int len = r - l + 1;
        int k = lg[len];
        int r0 = r - (1 << k) + 1;
        return betterNode(st[k][l], st[k][r0]).val;
    }
};

static inline void applyDominance(vector<int>& bestB, int n) {
    int curMin = INF;
    for (int a = 1; a <= n + 1; a++) {
        if (bestB[a] < curMin) curMin = bestB[a];
        else bestB[a] = INF;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n;
    vector<int> A(n + 1);
    for (int i = 1; i <= n; i++) cin >> A[i];
    cin >> m;
    vector<int> B(m + 1);
    for (int i = 1; i <= m; i++) cin >> B[i];
    cin >> k;

    vector<vector<uint16_t>> nxtA(n + 2, vector<uint16_t>(V + 1, 0));
    vector<vector<uint16_t>> nxtB(m + 2, vector<uint16_t>(V + 1, 0));

    for (int i = n; i >= 1; i--) {
        memcpy(nxtA[i].data(), nxtA[i + 1].data(), (V + 1) * sizeof(uint16_t));
        nxtA[i][A[i]] = (uint16_t)i;
    }
    for (int i = m; i >= 1; i--) {
        memcpy(nxtB[i].data(), nxtB[i + 1].data(), (V + 1) * sizeof(uint16_t));
        nxtB[i][B[i]] = (uint16_t)i;
    }

    SparseMin rmqA, rmqB;
    rmqA.build(A);
    rmqB.build(B);

    vector<vector<int>> cur(4, vector<int>(n + 2, INF));
    cur[0][1] = 1;
    applyDominance(cur[0], n);

    vector<int> ans;
    ans.reserve(k);

    for (int step = 0; step < k; step++) {
        int rem = k - (step + 1);
        int bestVal = INF;

        for (int mask = 0; mask < 4; mask++) {
            bool usedA = (mask & 2);
            bool usedB = (mask & 1);

            for (int aPos = 1; aPos <= n + 1; aPos++) {
                int bPos = cur[mask][aPos];
                if (bPos == INF) continue;

                if (aPos <= n) {
                    if (usedB || rem >= 1) {
                        if (usedB || bPos <= m) {
                            long long rhs = 1LL * n + m - bPos + 1 - rem;
                            int pmax = (int)min<long long>(n, rhs);
                            if (pmax >= aPos) {
                                bestVal = min(bestVal, rmqA.queryMin(aPos, pmax));
                            }
                        }
                    }
                }

                if (bPos <= m) {
                    if (usedA || rem >= 1) {
                        if (usedA || aPos <= n) {
                            long long rhs = 1LL * n + m - aPos + 1 - rem;
                            int qmax = (int)min<long long>(m, rhs);
                            if (qmax >= bPos) {
                                bestVal = min(bestVal, rmqB.queryMin(bPos, qmax));
                            }
                        }
                    }
                }
            }
        }

        ans.push_back(bestVal);

        vector<vector<int>> nxt(4, vector<int>(n + 2, INF));

        for (int mask = 0; mask < 4; mask++) {
            bool usedA = (mask & 2);
            bool usedB = (mask & 1);

            for (int aPos = 1; aPos <= n + 1; aPos++) {
                int bPos = cur[mask][aPos];
                if (bPos == INF) continue;

                if (aPos <= n) {
                    if (usedB || rem >= 1) {
                        if (usedB || bPos <= m) {
                            long long rhs = 1LL * n + m - bPos + 1 - rem;
                            int pmax = (int)min<long long>(n, rhs);
                            if (pmax >= aPos) {
                                uint16_t p = nxtA[aPos][bestVal];
                                if (p && (int)p <= pmax) {
                                    int nm = mask | 2;
                                    int na = (int)p + 1;
                                    nxt[nm][na] = min(nxt[nm][na], bPos);
                                }
                            }
                        }
                    }
                }

                if (bPos <= m) {
                    if (usedA || rem >= 1) {
                        if (usedA || aPos <= n) {
                            long long rhs = 1LL * n + m - aPos + 1 - rem;
                            int qmax = (int)min<long long>(m, rhs);
                            if (qmax >= bPos) {
                                uint16_t q = nxtB[bPos][bestVal];
                                if (q && (int)q <= qmax) {
                                    int nm = mask | 1;
                                    int nb = (int)q + 1;
                                    nxt[nm][aPos] = min(nxt[nm][aPos], nb);
                                }
                            }
                        }
                    }
                }
            }
        }

        for (int mask = 0; mask < 4; mask++) applyDominance(nxt[mask], n);
        cur.swap(nxt);
    }

    for (int i = 0; i < k; i++) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}
