#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;

static const int M1 = 1'000'000'007;
static const int M2 = 1'000'000'009;
static const int B  = 911382323; // base < M1, M2

struct PHash {
    size_t operator()(const pii& p) const noexcept {
        return (size_t)((uint64_t)(uint32_t)p.first << 32) ^ (uint32_t)p.second;
    }
};

vector<int> pw1 = {1}, pw2 = {1};

inline void ensure_pow(int n) {
    if ((int)pw1.size() > n) return;
    int cur = pw1.size();
    pw1.resize(n + 1);
    pw2.resize(n + 1);
    for (int i = cur; i <= n; ++i) {
        pw1[i] = (int)((1LL * pw1[i-1] * B) % M1);
        pw2[i] = (int)((1LL * pw2[i-1] * B) % M2);
    }
}

inline pii whole_hash(const string& s) {
    int h1 = 0, h2 = 0;
    for (char c : s) {
        int x = c - 'a' + 1;
        h1 = (int)(( (1LL * h1 * B) + x ) % M1);
        h2 = (int)(( (1LL * h2 * B) + x ) % M2);
    }
    return {h1, h2};
}

struct PrefHash {
    vector<int> h1, h2;
    void build(const string& s) {
        int n = (int)s.size();
        ensure_pow(n);
        h1.assign(n + 1, 0);
        h2.assign(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            int x = s[i] - 'a' + 1;
            h1[i+1] = (int)(( (1LL * h1[i] * B) + x ) % M1);
            h2[i+1] = (int)(( (1LL * h2[i] * B) + x ) % M2);
        }
    }
    inline pii sub(int l, int r) const {
        // [l, r], 0-indexed
        int len = r - l + 1;
        int x1 = (int)(( h1[r+1] - 1LL * h1[l] * pw1[len] ) % M1);
        if (x1 < 0) x1 += M1;
        int x2 = (int)(( h2[r+1] - 1LL * h2[l] * pw2[len] ) % M2);
        if (x2 < 0) x2 += M2;
        return {x1, x2};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int C, N;
    cin >> C >> N;

    unordered_set<pii, PHash> col, nam;
    col.reserve(C * 2);
    nam.reserve(N * 2);

    string s;

    for (int i = 0; i < C; ++i) {
        cin >> s;
        col.insert(whole_hash(s));
    }
    for (int i = 0; i < N; ++i) {
        cin >> s;
        nam.insert(whole_hash(s));
    }

    int Q;
    cin >> Q;

    PrefHash ph;
    while (Q--) {
        cin >> s;
        int L = (int)s.size();
        ph.build(s);

        bool ok = false;
        for (int i = 1; i < L && !ok; ++i) {
            // prefix [0..i-1] in colors AND suffix [i..L-1] in names
            if (col.find(ph.sub(0, i - 1)) != col.end() &&
                nam.find(ph.sub(i, L - 1)) != nam.end()) {
                ok = true;
            }
        }
        cout << (ok ? "Yes\n" : "No\n");
    }
    return 0;
}
