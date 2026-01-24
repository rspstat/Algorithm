#include <bits/stdc++.h>
using namespace std;

static const int T = 129600;

static inline uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
}

struct H {
    uint64_t a, b;
    bool operator==(const H& o) const { return a == o.a && b == o.b; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<H> A(T, {0, 0});
    vector<char> hasAngle(T, 0);

    for (int i = 0; i < n; i++) {
        long long rho;
        int phi;
        long long m;
        cin >> rho >> phi >> m;

        uint64_t x = (uint64_t)rho;
        uint64_t y = (uint64_t)m;
        uint64_t h1 = splitmix64(x ^ (y + 0x123456789abcdef0ULL));
        uint64_t h2 = splitmix64((x + 0x9e3779b97f4a7c15ULL) ^ (y + 0xfedcba9876543210ULL));

        A[phi] = {h1, h2};
        hasAngle[phi] = 1;
    }

    vector<H> Arev(T);
    for (int i = 0; i < T; i++) Arev[i] = A[(T - i) % T];

    vector<H> text;
    text.reserve(2 * T);
    for (int i = 0; i < T; i++) text.push_back(Arev[i]);
    for (int i = 0; i < T; i++) text.push_back(Arev[i]);

    vector<int> lps(T, 0);
    for (int i = 1, len = 0; i < T; ) {
        if (A[i] == A[len]) lps[i++] = ++len;
        else if (len) len = lps[len - 1];
        else lps[i++] = 0;
    }

    vector<int> Svals;
    Svals.reserve(T);

    for (int i = 0, j = 0; i < 2 * T; i++) {
        while (j > 0 && !(text[i] == A[j])) j = lps[j - 1];
        if (text[i] == A[j]) j++;
        if (j == T) {
            int start = i - (T - 1);
            if (0 <= start && start < T) {
                int S = (T - start) % T;
                Svals.push_back(S);
            }
            j = lps[j - 1];
        }
    }

    sort(Svals.begin(), Svals.end());
    Svals.erase(unique(Svals.begin(), Svals.end()), Svals.end());

    vector<long double> ans;
    ans.reserve((size_t)Svals.size() * 2);

    auto addAlpha = [&](int A2) {
        if (A2 % 2 == 0) {
            int ang = A2 / 2;
            if (hasAngle[ang]) return;
        }
        long double alpha = (long double)A2 / 2.0L;
        if (alpha < 0) alpha += (long double)T;
        if (alpha >= (long double)T) alpha -= (long double)T;
        ans.push_back(alpha);
    };

    for (int S : Svals) {
        addAlpha(S);
        addAlpha(S + T);
    }

    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end(), [](long double x, long double y){
        return fabsl(x - y) < 1e-12L;
    }), ans.end());

    cout << ans.size() << "\n";
    cout.setf(std::ios::fixed); cout << setprecision(10);
    for (auto v : ans) cout << (double)v << "\n";
    return 0;
}
