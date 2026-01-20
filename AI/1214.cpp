#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    // 입출력 속도 향상
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long D, P, Q;
    cin >> D >> P >> Q;

    // 더 큰 값을 P로 설정하여 반복 횟수를 최소화함
    if (P < Q) swap(P, Q);

    long long ans = 2e18; // 충분히 큰 값으로 초기화

    // i는 P를 사용하는 개수. 최대 Q번 또는 D/P + 1번까지만 확인하면 됨
    for (int i = 0; i <= min(D / P + 1, Q - 1); ++i) {
        long long current_p = (long long)i * P;
        long long remaining = D - current_p;

        if (remaining <= 0) {
            // P만으로 이미 D를 채웠으므로 현재 금액과 비교 후 종료
            ans = min(ans, current_p);
            break; 
        }

        // 남은 금액(remaining)을 Q로 채울 때 필요한 최소 개수 계산
        // ceiling(remaining / Q) 계산식: (remaining + Q - 1) / Q
        long long q_cnt = (remaining + Q - 1) / Q;
        long long total = current_p + q_cnt * Q;

        ans = min(ans, total);

        // 만약 정확히 D를 만들었다면 그보다 더 좋은 해는 없으므로 즉시 종료
        if (ans == D) break;
    }

    cout << ans << "\n";

    return 0;
}
