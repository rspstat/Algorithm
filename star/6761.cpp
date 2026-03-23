#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

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
    inline bool readInt(T& out) {
        char c;
        do { c = read(); if (!c) return false; } while (c <= ' ');
        bool neg = false;
        if (c == '-') { neg = true; c = read(); }
        long long v = 0;
        while (c > ' ') {
            v = v * 10 + (c - '0');
            c = read();
        }
        out = neg ? -v : v;
        return true;
    }
};

static inline int64 gcd64(int64 a, int64 b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b) { int64 t = a % b; a = b; b = t; }
    return a;
}
static inline int64 gcd3(int64 a, int64 b, int64 c) {
    return gcd64(gcd64(a, b), c);
}

struct Pt {
    int64 x, y;
};

struct F {
    int64 nr, ni, den;
    bool operator==(const F& o) const {
        return nr == o.nr && ni == o.ni && den == o.den;
    }
};

static vector<F> buildQ(const vector<Pt>& p) {
    int n = (int)p.size();
    vector<Pt> e(n);
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        e[i] = {p[j].x - p[i].x, p[j].y - p[i].y};
    }
    vector<F> q(n);
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        int64 ax = e[i].x, ay = e[i].y;
        int64 bx = e[j].x, by = e[j].y;

        __int128 nr = (__int128)bx * ax + (__int128)by * ay;
        __int128 ni = (__int128)by * ax - (__int128)bx * ay;
        __int128 den = (__int128)ax * ax + (__int128)ay * ay;

        int64 nrr = (int64)nr;
        int64 nii = (int64)ni;
        int64 dd  = (int64)den;

        int64 g = gcd3(nrr, nii, dd);
        nrr /= g; nii /= g; dd /= g;

        q[i] = {nrr, nii, dd};
    }
    return q;
}

static vector<int> kmpPi(const vector<F>& pat) {
    int n = (int)pat.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && !(pat[i] == pat[j])) j = pi[j - 1];
        if (pat[i] == pat[j]) j++;
        pi[i] = j;
    }
    return pi;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    FastIn in;
    int t;
    if (!in.readInt(t)) return 0;

    while (t--) {
        int n;
        in.readInt(n);

        vector<Pt> A(n), B(n);
        for (int i = 0; i < n; i++) {
            in.readInt(A[i].x);
            in.readInt(A[i].y);
        }
        for (int i = 0; i < n; i++) {
            in.readInt(B[i].x);
            in.readInt(B[i].y);
        }

        auto qA = buildQ(A);
        auto qB = buildQ(B);

        vector<F> text(2 * n);
        for (int i = 0; i < 2 * n; i++) text[i] = qB[i % n];

        auto pi = kmpPi(qA);

        int j = 0;
        int ans = 0;
        for (int i = 0; i < 2 * n; i++) {
            while (j > 0 && !(text[i] == qA[j])) j = pi[j - 1];
            if (text[i] == qA[j]) j++;
            if (j == n) {
                int start = i - n + 1;
                if (start < n) {
                    ans = start + 1;
                    break;
                }
                j = pi[j - 1];
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
