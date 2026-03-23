#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// KMP의 실패 함수(Failure Function) 생성
vector<int> getPi(const vector<int>& p) {
    int m = p.size();
    vector<int> pi(m, 0);
    
    int begin = 1, matched = 0;
    while (begin + matched < m) {
        if (p[begin + matched] == p[matched]) {
            matched++;
            pi[begin + matched - 1] = matched;
        }
        else {
            if (matched == 0)
                begin++;
            else {
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }
    return pi;
}

int main() {
    // 입출력 속도 향상
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // 뒤쪽(Suffix) 패턴을 찾아야 하므로 배열을 뒤집습니다.
    reverse(arr.begin(), arr.end());

    // 뒤집은 배열에 대해 Pi 배열 계산
    vector<int> pi = getPi(arr);

    int best_k = n - 1;
    int best_p = 1;
    int min_total = n; // K + P의 최소값 (초기값: 넉넉하게 잡음)

    // 모든 가능한 접미사 길이(reversed 기준 접두사 길이)에 대해 탐색
    // i는 reversed 배열의 인덱스 (길이는 i+1)
    for (int i = 0; i < n; i++) {
        int len = i + 1;
        int p_val = len - pi[i]; // 주기 P
        int k_val = n - len;     // 버리는 부분 K
        int total = k_val + p_val;

        // 1. 합(K+P)이 더 작으면 갱신
        if (total < min_total) {
            min_total = total;
            best_k = k_val;
            best_p = p_val;
        }
        // 2. 합이 같다면 P가 더 작은 쪽으로 갱신
        else if (total == min_total) {
            if (p_val < best_p) {
                best_k = k_val;
                best_p = p_val;
            }
        }
    }

    cout << best_k << " " << best_p << "\n";

    return 0;
}
