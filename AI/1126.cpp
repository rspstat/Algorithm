#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset, memcpy

using namespace std;

// 문제의 테스트 데이터상 높이의 총합은 500,000을 넘지 않습니다.
const int MAX_SUM = 500000;

// dp[d] = 두 탑의 높이 차이가 d일 때, 큰 쪽 탑의 최대 높이
int dp[MAX_SUM + 1];
int next_dp[MAX_SUM + 1];

int main() {
    // 입출력 속도 향상
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> h(n);
    for (int i = 0; i < n; ++i) {
        cin >> h[i];
    }

    // DP 배열 초기화 (-1은 도달 불가능한 상태를 의미)
    memset(dp, -1, sizeof(dp));
    dp[0] = 0; // 초기 상태: 높이 차이 0, 높이 0

    for (int i = 0; i < n; ++i) {
        int height = h[i];
        
        // 이번 블록을 사용하지 않는 경우를 포함하기 위해 현재 dp 상태를 복사
        memcpy(next_dp, dp, sizeof(dp));

        for (int diff = 0; diff <= MAX_SUM; ++diff) {
            // 도달할 수 없는 상태는 건너뜀
            if (dp[diff] == -1) continue;

            // 1. 더 높은 탑에 블록을 쌓는 경우
            // 높이 차이가 더 벌어짐
            if (diff + height <= MAX_SUM) {
                next_dp[diff + height] = max(next_dp[diff + height], dp[diff] + height);
            }

            // 2. 더 낮은 탑에 블록을 쌓는 경우
            if (diff >= height) {
                // 블록을 쌓아도 여전히 원래 높은 탑이 더 높은 경우 (혹은 같아짐)
                // 높이 차이는 줄어들고, 큰 탑의 높이(dp[diff])는 그대로임
                next_dp[diff - height] = max(next_dp[diff - height], dp[diff]);
            } else {
                // 블록을 쌓아서 낮은 탑이 더 높아지는 경우 (역전)
                // 새로운 높이 차이: height - diff
                // 새로운 큰 탑의 높이: (원래 작은 탑 높이) + height
                // 원래 작은 탑 높이 = dp[diff] - diff
                next_dp[height - diff] = max(next_dp[height - diff], dp[diff] - diff + height);
            }
        }
        
        // 갱신된 DP 배열을 다음 단계로 넘김
        memcpy(dp, next_dp, sizeof(dp));
    }

    // 높이 차이가 0일 때의 최대 높이 출력
    if (dp[0] > 0) {
        cout << dp[0] << endl;
    } else {
        // 불가능한 경우
        cout << -1 << endl;
    }

    return 0;
}
