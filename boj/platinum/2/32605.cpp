#include <bits/stdc++.h>
using namespace std;

static inline uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
}

struct RH {
    int n;
    uint64_t B;
    vector<uint64_t> pw, pref;

    RH() : n(0), B(0) {}
    RH(const string& s, uint64_t base) { init(s, base); }

    void init(const string& s, uint64_t base) {
        n = (int)s.size();
        B = base;
        pw.assign(n + 1, 0);
        pref.assign(n + 1, 0);
        pw[0] = 1;
        for (int i = 0; i < n; i++) {
            pw[i + 1] = pw[i] * B;
            pref[i + 1] = pref[i] * B + (uint64_t)(s[i] - 'a' + 1);
        }
    }

    uint64_t get(int l, int r) const {
        return pref[r] - pref[l] * pw[r - l];
    }
};

struct KeyPos {
    uint64_t h1, h2;
    int pos;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = (int)s.size();

    uint64_t seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    uint64_t b1 = splitmix64(seed) | 1ULL;
    uint64_t b2 = splitmix64(seed ^ 0x123456789abcdef0ULL) | 1ULL;

    RH rh1(s, b1), rh2(s, b2);

    int ans = n + 1;

    vector<KeyPos> a;
    vector<int> posbuf;
    a.reserve(n);
    posbuf.reserve(n);

    for (int L = 1; L <= n; L++) {
        int m = n - L + 1;
        a.clear();
        a.resize(m);
        for (int i = 0; i < m; i++) {
            a[i] = { rh1.get(i, i + L), rh2.get(i, i + L), i };
        }

        sort(a.begin(), a.end(), [](const KeyPos& x, const KeyPos& y) {
            if (x.h1 != y.h1) return x.h1 < y.h1;
            if (x.h2 != y.h2) return x.h2 < y.h2;
            return x.pos < y.pos;
        });

        int i = 0;
        while (i < m) {
            int j = i;
            while (j < m && a[j].h1 == a[i].h1 && a[j].h2 == a[i].h2) j++;

            posbuf.clear();
            posbuf.reserve(j - i);
            for (int k = i; k < j; k++) posbuf.push_back(a[k].pos);
            sort(posbuf.begin(), posbuf.end());

            int cnt = 0;
            int last = -1000000000;
            for (int p : posbuf) {
                if (p >= last + L) {
                    cnt++;
                    last = p;
                }
            }

            int total = L + (n - cnt * (L - 1));
            if (total < ans) ans = total;

            i = j;
        }
    }

    cout << ans << "\n";
    return 0;
}
