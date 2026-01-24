#include <bits/stdc++.h>
using namespace std;

static const uint64_t B1 = 911382323u;
static const uint64_t B2 = 972663749u;

struct FastIn {
    static const int SZ = 1 << 20;
    int idx = 0, size = 0;
    char buf[SZ];
    inline char read() {
        if (idx >= size) {
            size = (int)fread(buf, 1, SZ, stdin);
            idx = 0;
            if (!size) return 0;
        }
        return buf[idx++];
    }
    template <class T>
    inline bool readInt(T &out) {
        char c;
        do { c = read(); if (!c) return false; } while (c <= ' ');
        bool neg = false;
        if (c == '-') { neg = true; c = read(); }
        T val = 0;
        while (c > ' ') {
            val = val * 10 + (c - '0');
            c = read();
        }
        out = neg ? -val : val;
        return true;
    }
    inline char readLower() {
        char c;
        do { c = read(); } while (c && (c < 'a' || c > 'z'));
        return c;
    }
};

struct Key {
    uint64_t a, b;
    bool operator==(const Key& o) const { return a == o.a && b == o.b; }
};
struct KeyHash {
    size_t operator()(const Key& k) const noexcept {
        uint64_t x = k.a ^ (k.b + 0x9e3779b97f4a7c15ULL + (k.a << 6) + (k.a >> 2));
        return (size_t)x;
    }
};

struct MinPair {
    unsigned char ch;
    int pos;
};
static inline MinPair better(const MinPair& x, const MinPair& y) {
    if (x.ch != y.ch) return (x.ch < y.ch) ? x : y;
    return (x.pos < y.pos) ? x : y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    FastIn in;

    int N, M, K;
    if (!in.readInt(N)) return 0;
    in.readInt(M);
    in.readInt(K);

    int S = M - K;
    vector<unsigned char> grid((size_t)N * (size_t)M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            char c = in.readLower();
            grid[(size_t)i * M + j] = (unsigned char)c;
        }
    }

    string out;
    out.reserve((size_t)N * (size_t)S);

    vector<unsigned char> row1(M);
    for (int j = 0; j < M; j++) row1[j] = grid[j];

    vector<unsigned char> st;
    st.reserve(M);
    int rem = K;
    for (int j = 0; j < M; j++) {
        unsigned char c = row1[j];
        while (!st.empty() && rem > 0 && st.back() > c) {
            st.pop_back();
            rem--;
        }
        st.push_back(c);
    }
    while (rem > 0 && !st.empty()) {
        st.pop_back();
        rem--;
    }
    if ((int)st.size() > S) st.resize(S);

    vector<unsigned char> patRow(S);
    for (int i = 0; i < S; i++) patRow[i] = st[i];
    out.append((const char*)patRow.data(), (size_t)S);

    vector<uint64_t> colH1(M), colH2(M);
    for (int j = 0; j < M; j++) {
        uint64_t v = (uint64_t)(row1[j] - 'a' + 1);
        colH1[j] = v;
        colH2[j] = v;
    }

    vector<uint64_t> patH1(S), patH2(S);
    for (int i = 0; i < S; i++) {
        uint64_t v = (uint64_t)(patRow[i] - 'a' + 1);
        patH1[i] = v;
        patH2[i] = v;
    }

    vector<int> colId(M), patId(S), latest(S);
    vector<unsigned char> curRow(M);
    vector<unsigned char> newPatRow(S);
    vector<uint64_t> newPatH1(S), newPatH2(S);

    for (int r = 1; r < N; r++) {
        for (int j = 0; j < M; j++) curRow[j] = grid[(size_t)r * M + j];

        unordered_map<Key, int, KeyHash> mp;
        mp.reserve((size_t)M * 2);
        mp.max_load_factor(0.7f);

        vector<vector<int>> pos;
        pos.reserve(M);

        int idCnt = 0;
        for (int j = 0; j < M; j++) {
            Key k{colH1[j], colH2[j]};
            auto it = mp.find(k);
            int id;
            if (it == mp.end()) {
                id = idCnt++;
                mp.emplace(k, id);
                pos.emplace_back();
            } else {
                id = it->second;
            }
            colId[j] = id;
            pos[id].push_back(j);
        }

        for (int k = 0; k < S; k++) {
            Key kk{patH1[k], patH2[k]};
            patId[k] = mp.find(kk)->second;
        }

        int cur = M - 1;
        for (int k = S - 1; k >= 0; k--) {
            int need = patId[k];
            while (cur >= 0 && colId[cur] != need) cur--;
            latest[k] = cur;
            cur--;
        }

        vector<char> used(idCnt, 0);
        for (int k = 0; k < S; k++) used[patId[k]] = 1;

        struct SegTree {
            int base;
            vector<MinPair> seg;
        };
        vector<SegTree> segs(idCnt);

        for (int id = 0; id < idCnt; id++) {
            if (!used[id]) continue;
            int sz = (int)pos[id].size();
            if (sz <= 1) continue;
            int base = 1;
            while (base < sz) base <<= 1;
            segs[id].base = base;
            segs[id].seg.assign(2 * base, MinPair{255, INT_MAX});
            for (int i = 0; i < sz; i++) {
                int p = pos[id][i];
                segs[id].seg[base + i] = MinPair{(unsigned char)(curRow[p]), p};
            }
            for (int i = base - 1; i >= 1; i--) {
                segs[id].seg[i] = better(segs[id].seg[i << 1], segs[id].seg[i << 1 | 1]);
            }
        }

        auto query = [&](int id, int lidx, int ridx) -> MinPair {
            const auto& stt = segs[id];
            int L = lidx + stt.base;
            int R = ridx + stt.base;
            MinPair res{255, INT_MAX};
            while (L <= R) {
                if (L & 1) res = better(res, stt.seg[L++]);
                if (!(R & 1)) res = better(res, stt.seg[R--]);
                L >>= 1;
                R >>= 1;
            }
            return res;
        };

        int prevPos = -1;
        for (int k = 0; k < S; k++) {
            int id = patId[k];
            const auto& occ = pos[id];
            int lim = latest[k];

            int li = (int)(lower_bound(occ.begin(), occ.end(), prevPos + 1) - occ.begin());
            int ri = (int)(upper_bound(occ.begin(), occ.end(), lim) - occ.begin()) - 1;

            MinPair best;
            if ((int)occ.size() == 1) {
                int p = occ[0];
                best = MinPair{(unsigned char)curRow[p], p};
            } else {
                best = query(id, li, ri);
            }
            newPatRow[k] = best.ch;
            prevPos = best.pos;
        }

        out.append((const char*)newPatRow.data(), (size_t)S);

        for (int k = 0; k < S; k++) {
            uint64_t v = (uint64_t)(newPatRow[k] - 'a' + 1);
            newPatH1[k] = patH1[k] * B1 + v;
            newPatH2[k] = patH2[k] * B2 + v;
        }
        patH1.swap(newPatH1);
        patH2.swap(newPatH2);

        for (int j = 0; j < M; j++) {
            uint64_t v = (uint64_t)(curRow[j] - 'a' + 1);
            colH1[j] = colH1[j] * B1 + v;
            colH2[j] = colH2[j] * B2 + v;
        }
    }

    cout << out << "\n";
    return 0;
}
