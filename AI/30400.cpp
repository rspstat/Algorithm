#include <bits/stdc++.h>
using namespace std;

struct Seg {
    int l, r;
};

static vector<int> manacher_odd(const string& s) {
    int n = (int)s.size();
    vector<int> d(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : min(d[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) k++;
        d[i] = k;
        if (i + k - 1 > r) {
            l = i - k + 1;
            r = i + k - 1;
        }
    }
    return d;
}

static vector<int> manacher_even(const string& s) {
    int n = (int)s.size();
    vector<int> d(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 0 : min(d[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) k++;
        d[i] = k;
        if (i + k - 1 > r) {
            l = i - k;
            r = i + k - 1;
        }
    }
    return d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    string s;
    cin >> s;

    auto d1 = manacher_odd(s);
    auto d2 = manacher_even(s);

    int needOdd = (M + 2) / 2;
    int needEven = (M + 1) / 2;

    vector<Seg> segs;
    segs.reserve(2 * N);

    for (int i = 0; i < N; i++) {
        if (d1[i] >= needOdd) {
            int k = needOdd;
            int l = i - (k - 1);
            int r = i + (k - 1);
            segs.push_back({l, r});
        }
    }
    for (int i = 0; i < N; i++) {
        if (d2[i] >= needEven) {
            int k = needEven;
            int l = i - k;
            int r = i + k - 1;
            segs.push_back({l, r});
        }
    }

    if (segs.empty()) {
        cout << 0 << "\n";
        return 0;
    }

    sort(segs.begin(), segs.end(), [&](const Seg& a, const Seg& b) {
        if (a.r != b.r) return a.r < b.r;
        return a.l < b.l;
    });

    int ans = 0;
    int last = -1;

    for (auto &g : segs) {
        if (last < g.l) {
            last = g.r;
            ans++;
        }
    }

    cout << ans << "\n";
    return 0;
}
