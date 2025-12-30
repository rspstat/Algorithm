#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int n, d;
int sa[1000005], pos[1000005], tmp[1000005], lcp[1000005];
string s;

// Manber-Myers 알고리즘을 위한 비교 함수
bool cmp(int i, int j) {
    if (pos[i] != pos[j]) return pos[i] < pos[j];
    int ri = (i + d < n) ? pos[i + d] : -1;
    int rj = (j + d < n) ? pos[j + d] : -1;
    return ri < rj;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> s;
    n = s.size();

    for (int i = 0; i < n; i++) {
        sa[i] = i;
        pos[i] = s[i];
    }

    // Suffix Array 생성 (O(N log^2 N))
    for (d = 1; d < n; d <<= 1) {
        sort(sa, sa + n, cmp);

        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            if (cmp(sa[i - 1], sa[i])) tmp[sa[i]] = tmp[sa[i - 1]] + 1;
            else tmp[sa[i]] = tmp[sa[i - 1]];
        }
        for (int i = 0; i < n; i++) pos[i] = tmp[i];
        
        if (pos[sa[n - 1]] == n - 1) break;
    }

    // LCP Array 생성 (Kasai's Algorithm, O(N))
    for (int i = 0, k = 0; i < n; i++) {
        if (pos[i] == 0) continue;
        int j = sa[pos[i] - 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
        lcp[pos[i]] = k;
        if (k) k--;
    }

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        // 각 접미사 길이에서 이전 접미사와 겹치는 길이(LCP)만큼 제외
        ans += (long long)(n - sa[i]) - lcp[i];
    }

    cout << ans;

    return 0;
}
