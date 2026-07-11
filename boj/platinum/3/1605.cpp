#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

const int MAX_L = 200005;

int n;
string s;
int sa[MAX_L];      // Suffix Array: 정렬된 접미사의 시작 인덱스
int pos[MAX_L];     // Rank Array: 각 접미사의 순위 (Inverse SA)
int tmp[MAX_L];     // 정렬을 위한 임시 배열
int lcp[MAX_L];     // LCP Array: 인접한 접미사 간의 최장 공통 접두사 길이
int gap;            // 비교할 간격 (1, 2, 4, 8 ...)

// Suffix 비교 함수 (첫 번째 기준: pos[i], 두 번째 기준: pos[i+gap])
bool compareSA(int a, int b) {
    if (pos[a] != pos[b]) return pos[a] < pos[b];
    
    int rankA = (a + gap < n) ? pos[a + gap] : -1;
    int rankB = (b + gap < n) ? pos[b + gap] : -1;
    return rankA < rankB;
}

// Suffix Array 생성 (Manber-Myers Algorithm, O(N log^2 N))
void buildSA() {
    for (int i = 0; i < n; i++) {
        sa[i] = i;
        pos[i] = s[i]; // 초기 순위는 첫 글자 아스키코드
    }

    // gap을 2배씩 늘려가며 정렬
    for (gap = 1; gap < n; gap <<= 1) {
        sort(sa, sa + n, compareSA);

        // 정렬 후 순위(pos) 갱신
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            // 앞의 접미사와 순위가 같다면 같은 그룹
            if (compareSA(sa[i - 1], sa[i])) {
                tmp[sa[i]] = tmp[sa[i - 1]] + 1;
            } else {
                tmp[sa[i]] = tmp[sa[i - 1]];
            }
        }
        for (int i = 0; i < n; i++) pos[i] = tmp[i];

        // 모든 접미사의 순위가 다르면 조기 종료
        if (pos[sa[n - 1]] == n - 1) break;
    }
}

// LCP Array 생성 (Kasai's Algorithm, O(N))
void buildLCP() {
    for (int i = 0, len = 0; i < n; i++) {
        // i번째 접미사의 순위
        int rank = pos[i];
        
        // 마지막 순위의 접미사는 비교 대상이 없으므로 패스
        if (rank == n - 1) {
            len = 0;
            continue;
        }

        // SA상에서 바로 다음 순위의 접미사 시작 위치
        int j = sa[rank + 1];

        // 문자열 매칭 (이전 매칭 길이 len부터 시작)
        while (i + len < n && j + len < n && s[i + len] == s[j + len]) {
            len++;
        }

        lcp[rank] = len;

        // 다음 접미사로 넘어갈 때, 겹치는 부분은 최소 len-1 만큼 보장됨
        if (len > 0) len--;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> s;

    buildSA();
    buildLCP();

    int maxLen = 0;
    // LCP 배열 중 최댓값이 정답 (단, 마지막 인덱스는 의미 없으므로 n-1까지만 확인)
    for (int i = 0; i < n - 1; i++) {
        if (lcp[i] > maxLen) {
            maxLen = lcp[i];
        }
    }

    cout << maxLen << "\n";

    return 0;
}
