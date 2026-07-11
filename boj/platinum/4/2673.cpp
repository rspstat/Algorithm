#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 점의 최대 개수는 100개
int dp[101][101];
bool hasChord[101][101];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        int u, v;
        cin >> u >> v;
        // 항상 u < v가 되도록 정렬하여 저장
        if (u > v) swap(u, v);
        hasChord[u][v] = true;
    }

    // 구간의 길이(len)를 1부터 100까지 늘려가며 DP 수행
    for (int len = 1; len <= 100; len++) {
        for (int i = 1; i <= 100 - len; i++) {
            int j = i + len;
            
            // 1. 구간을 k를 기준으로 나누어 최댓값 갱신
            for (int k = i; k < j; k++) {
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[k + 1][j]);
            }
            
            // 2. 현재 구간의 양 끝점 (i, j)를 잇는 현이 있다면 +1
            if (hasChord[i][j]) {
                dp[i][j]++;
            }
        }
    }

    // 전체 범위 [1, 100]에서의 최댓값 출력
    cout << dp[1][100] << "\n";

    return 0;
}
