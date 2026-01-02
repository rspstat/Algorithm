#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int MAX = 500005;
int n, d;
string s;
int sa[MAX], pos[MAX], tmp[MAX];
int lcp[MAX];

// Manber-Myers 알고리즘을 위한 비교 함수
// (pos[i], pos[i+d]) 쌍을 기준으로 비교
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
    n = s.length();

    // 1. Suffix Array 구성 (O(N log^2 N))
    for (int i = 0; i < n; i++) {
        sa[i] = i;
        pos[i] = s[i]; // 첫 글자로 초기 순위 설정
    }

    for (d = 1; ; d <<= 1) {
        sort(sa, sa + n, cmp);

        // 정렬된 상태를 기반으로 새로운 순위(Rank) 부여
        // tmp 배열에 임시 저장 후 pos에 반영
        tmp[0] = 0;
        for (int i = 1; i < n; i++) {
            if (cmp(sa[i - 1], sa[i])) tmp[i] = tmp[i - 1] + 1;
            else tmp[i] = tmp[i - 1];
        }

        for (int i = 0; i < n; i++) pos[sa[i]] = tmp[i];

        // 모든 접미사의 순위가 달라지면 정렬 완료
        if (tmp[n - 1] == n - 1) break;
    }

    // Suffix Array 출력 (1-based index)
    for (int i = 0; i < n; i++) cout << sa[i] + 1 << " ";
    cout << "\n";

    // 2. LCP Array 구성 (Kasai's Algorithm, O(N))
    // pos[i]는 i번째 접미사의 Suffix Array 내 순위(Rank)
    // lcp[k]는 Suffix Array에서 k-1번째 접미사와 k번째 접미사의 LCP 길이
    
    for (int i = 0, k = 0; i < n; i++) {
        // SA에서 첫 번째로 오는 접미사는 비교할 앞 순서가 없으므로 패스
        if (pos[i] == 0) continue; 

        // SA상에서 바로 앞 순서에 있는 접미사의 시작 위치
        int j = sa[pos[i] - 1]; 

        // 같은 문자가 나올 때까지 k 증가
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
        
        lcp[pos[i]] = k;

        // 다음 접미사(i+1)는 현재(i)보다 앞부분 한 글자가 빠지므로
        // LCP가 최소 k-1 이상임이 보장됨
        if (k > 0) k--;
    }

    // LCP Array 출력
    cout << "x ";
    for (int i = 1; i < n; i++) cout << lcp[i] << " ";

    return 0;
}
