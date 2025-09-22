#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    vector<int> t;           // t[len-1] = 길이 len인 증가 부분 수열의 최소 끝값
    t.reserve(n);

    for (int x : a) {
        // 엄격 증가(LIS): 첫 >= x 위치를 치환(lower_bound)
        auto it = lower_bound(t.begin(), t.end(), x);
        if (it == t.end()) t.push_back(x);
        else *it = x;
    }

    cout << (int)t.size() << '\n';
    return 0;
}
