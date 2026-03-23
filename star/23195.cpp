#include <bits/stdc++.h>
using namespace std;

static string fold_left(const string& x) {
    int n = (int)x.size();
    if (n <= 1) return x;

    string s;
    s.reserve(2 * n - 1);
    s.push_back(x[0]);
    for (int i = 1; i < n; i++) {
        s.push_back('#');
        s.push_back(x[i]);
    }

    int m = (int)s.size();
    vector<int> rad(m, 0);

    int c = 0, r = 0;
    int hh = 0;

    for (int i = 0; i < m; i++) {
        int len = 0;
        if (i <= r) {
            int j = 2 * c - i;
            len = min(r - i, (j >= 0 && j < m) ? rad[j] : 0);
        }
        while (i + len + 1 < m && i - len - 1 >= hh && s[i + len + 1] == s[i - len - 1]) len++;
        rad[i] = len;
        if (i + len > r) {
            c = i;
            r = i + len;
        }
        if (s[i] == '#' && i - rad[i] <= hh) hh = i;
    }

    string res;
    res.reserve(n);
    for (int i = hh; i < m; i++) {
        if (s[i] != '#') res.push_back(s[i]);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string dna;
    cin >> dna;

    string a = fold_left(dna);
    reverse(a.begin(), a.end());
    string b = fold_left(a);

    cout << b.size() << "\n";
    return 0;
}
