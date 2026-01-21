#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string N_str;
int K;
string ans_str;

// 비트마스크에 포함된 1의 개수(서로 다른 숫자의 개수)를 세는 함수
int count_set_bits(int n) {
    int count = 0;
    while (n > 0) {
        if (n & 1) count++;
        n >>= 1;
    }
    return count;
}

// idx: 현재 채우고 있는 인덱스
// len: 목표 자릿수
// tight: N보다 큰 것이 확정되지 않아 N의 자릿수에 제약을 받는 상태인지 여부
// mask: 현재까지 사용한 숫자들의 비트마스크
// current: 현재까지 만들어진 문자열
bool dfs(int idx, int len, bool tight, int mask, string& current) {
    int distinct_count = count_set_bits(mask);

    // 가지치기 1: 이미 K개보다 많은 종류의 숫자를 사용한 경우
    if (distinct_count > K) return false;
    
    // 가지치기 2: 남은 자릿수를 모두 새로운 숫자로 채워도 K개를 채울 수 없는 경우
    if (distinct_count + (len - idx) < K) return false;

    // 기저 사례: 목표 길이에 도달한 경우
    if (idx == len) {
        return distinct_count == K;
    }

    // 탐색 시작 숫자 결정
    int start = 0;
    if (tight) {
        start = N_str[idx] - '0';
    } else {
        if (idx == 0) start = 1; // 맨 앞자리는 0이 올 수 없음 (자릿수가 늘어난 경우)
        else start = 0;
    }

    // 가능한 숫자(start ~ 9)를 순회하며 탐색
    for (int d = start; d <= 9; ++d) {
        // 다음 상태 계산
        // tight 유지 조건: 현재 tight 상태이고, 이번에 고른 숫자가 경계값(start)과 같을 때만 유지됨
        bool next_tight = tight && (d == start);
        int next_mask = mask | (1 << d);
        
        current.push_back(d + '0');
        
        // 재귀 호출: 답을 찾으면 즉시 true 반환 (최소값을 찾아야 하므로)
        if (dfs(idx + 1, len, next_tight, next_mask, current)) {
            return true;
        }
        
        // 백트래킹
        current.pop_back();
    }
    
    return false;
}

int main() {
    // 입출력 속도 향상
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> N_str >> K)) return 0;

    // N의 길이부터 시작하여 가능한 최소 길이를 탐색 (최대 19~20자리까지 안전하게 탐색)
    for (int len = N_str.length(); len <= 20; ++len) {
        ans_str = "";
        
        // 자릿수가 N과 같을 때만 tight 제약이 있음
        bool tight = (len == N_str.length());
        
        if (dfs(0, len, tight, 0, ans_str)) {
            cout << ans_str << endl;
            return 0;
        }
    }

    return 0;
}
