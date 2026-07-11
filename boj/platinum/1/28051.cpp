#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string t;
    int D;
    cin >> t >> D;
    int n = (int)t.size();

    vector<int> kmp(n, 0);

    auto calc = [&](int start) -> int {
        kmp[start] = start;
        int j = start;
        for (int i = start + 1; i < n; i++) {
            while (j > start && t[i] != t[j]) j = kmp[j - 1];
            if (t[i] == t[j]) j++;
            kmp[i] = j;
            if (i - kmp[i] >= D) return i;
        }
        return n;
    };

    int pos = 0, ans = 0;
    while (pos < n) {
        ans++;
        if (pos + D >= n) break;
        pos = calc(pos);
    }

    cout << ans << '\n';
    return 0;
}
