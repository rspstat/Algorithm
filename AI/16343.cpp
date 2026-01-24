#include <bits/stdc++.h>
using namespace std;

static vector<int> build_sa(const string& s) {
    int n = (int)s.size();
    vector<int> sa(n), r(n), tmp(n);

    int m = max(256, n) + 1;
    vector<int> cnt(m);

    for (int i = 0; i < n; i++) r[i] = (unsigned char)s[i];
    iota(sa.begin(), sa.end(), 0);

    for (int k = 1;; k <<= 1) {
        auto radix = [&](auto keyMax) {
            fill(cnt.begin(), cnt.end(), 0);
            for (int i = 0; i < n; i++) cnt[keyMax[i]]++;
            for (int i = 1; i < (int)cnt.size(); i++) cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; i--) tmp[--cnt[keyMax[sa[i]]]] = sa[i];
            sa.swap(tmp);
        };

        vector<int> key2(n), key1(n);
        for (int i = 0; i < n; i++) {
            int j = sa[i];
            key2[j] = (j + k < n) ? (r[j + k] + 1) : 0;
        }
        int max2 = 0;
        for (int i = 0; i < n; i++) max2 = max(max2, key2[i]);
        cnt.assign(max(max2 + 1, 1), 0);
        fill(cnt.begin(), cnt.end(), 0);
        for (int i = 0; i < n; i++) cnt[key2[i]]++;
        for (int i = 1; i < (int)cnt.size(); i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) tmp[--cnt[key2[sa[i]]]] = sa[i];
        sa.swap(tmp);

        for (int i = 0; i < n; i++) key1[i] = r[i] + 1;
        int max1 = 0;
        for (int i = 0; i < n; i++) max1 = max(max1, key1[i]);
        cnt.assign(max(max1 + 1, 1), 0);
        fill(cnt.begin(), cnt.end(), 0);
        for (int i = 0; i < n; i++) cnt[key1[i]]++;
        for (int i = 1; i < (int)cnt.size(); i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) tmp[--cnt[key1[sa[i]]]] = sa[i];
        sa.swap(tmp);

        tmp[sa[0]] = 0;
        int classes = 1;
        for (int i = 1; i < n; i++) {
            int a = sa[i - 1], b = sa[i];
            int a1 = r[a], b1 = r[b];
            int a2 = (a + k < n) ? r[a + k] : -1;
            int b2 = (b + k < n) ? r[b + k] : -1;
            if (a1 != b1 || a2 != b2) classes++;
            tmp[b] = classes - 1;
        }
        r.swap(tmp);
        if (classes == n) break;
    }
    return sa;
}

static vector<int> build_lcp(const string& s, const vector<int>& sa, vector<int>& rk) {
    int n = (int)s.size();
    rk.assign(n, 0);
    for (int i = 0; i < n; i++) rk[sa[i]] = i;

    vector<int> lcp(n, 0);
    for (int i = 0, k = 0; i < n; i++) {
        int r = rk[i];
        if (r == 0) { k = 0; continue; }
        int j = sa[r - 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
        lcp[r] = k;
        if (k) k--;
    }
    return lcp;
}

struct RMQ {
    int n;
    vector<int> lg;
    vector<vector<int>> st;

    RMQ() : n(0) {}

    RMQ(const vector<int>& a) { build(a); }

    void build(const vector<int>& a) {
        n = (int)a.size();
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
        int K = lg[n] + 1;
        st.assign(K, vector<int>(n));
        st[0] = a;
        for (int k = 1; k < K; k++) {
            int len = 1 << k;
            int half = len >> 1;
            for (int i = 0; i + len <= n; i++) {
                st[k][i] = min(st[k - 1][i], st[k - 1][i + half]);
            }
        }
    }

    int query(int l, int r) const {
        if (l > r) return INT_MAX;
        int len = r - l + 1;
        int k = lg[len];
        return min(st[k][l], st[k][r - (1 << k) + 1]);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;
    string s;
    cin >> s;
    string s2 = s + s;
    int L = (int)s2.size();

    auto sa = build_sa(s2);
    vector<int> rk;
    auto lcp = build_lcp(s2, sa, rk);
    RMQ rmq(lcp);

    vector<int> starts(N);
    iota(starts.begin(), starts.end(), 0);
    sort(starts.begin(), starts.end(), [&](int a, int b){
        return rk[a] < rk[b];
    });

    auto lcp_pos = [&](int a, int b) -> int {
        if (a == b) return L - a;
        int ra = rk[a], rb = rk[b];
        if (ra > rb) swap(ra, rb);
        return rmq.query(ra + 1, rb);
    };

    auto leq_sub = [&](int i, int p) -> bool {
        if (i == p) return true;
        int l = lcp_pos(i, p);
        if (l >= K) return true;
        unsigned char a = (unsigned char)s2[i + l];
        unsigned char b = (unsigned char)s2[p + l];
        return a < b;
    };

    auto feasible = [&](int mid) -> bool {
        int p = starts[mid];
        int first = -1, last = -1, maxGap = 0;
        for (int i = 0; i < N; i++) {
            if (leq_sub(i, p)) {
                if (first == -1) first = i;
                if (last != -1) maxGap = max(maxGap, i - last);
                last = i;
            }
        }
        if (first == -1) return false;
        maxGap = max(maxGap, first + N - last);
        return maxGap <= K;
    };

    int lo = 0, hi = N - 1;
    while (lo < hi) {
        int mid = (lo + hi) >> 1;
        if (feasible(mid)) hi = mid;
        else lo = mid + 1;
    }

    int p = starts[lo];
    cout << s2.substr(p, K) << "\n";
    return 0;
}
