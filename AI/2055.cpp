#include <iostream>
#include <numeric> // std::gcd

using namespace std;

// 조합 nC3 계산 함수
long long combination3(long long n) {
    if (n < 3) return 0;
    return n * (n - 1) * (n - 2) / 6;
}

// 최대공약수 함수 (C++17 이상은 std::gcd 사용 가능, 그 외는 직접 구현)
long long get_gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int main() {
    // 입출력 속도 향상
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long N, M;
    if (!(cin >> N >> M)) return 0;

    // 1. 전체 점의 개수
    long long total_points = (N + 1) * (M + 1);

    // 2. 전체 경우의 수 (Total C 3)
    long long ans = combination3(total_points);

    // 3. 일직선상의 점 3개인 경우 제외

    // (1) 가로줄 (행)
    // 각 행에는 N+1개의 점이 있음. 행의 개수는 M+1개.
    ans -= (M + 1) * combination3(N + 1);

    // (2) 세로줄 (열)
    // 각 열에는 M+1개의 점이 있음. 열의 개수는 N+1개.
    ans -= (N + 1) * combination3(M + 1);

    // (3) 대각선
    // 가로 차이 i, 세로 차이 j인 두 점 사이의 점 개수: gcd(i, j) - 1
    // 이를 통해 만들어지는 일직선 3점의 쌍을 모두 제거
    for (long long i = 1; i <= N; i++) {
        for (long long j = 1; j <= M; j++) {
            long long count = get_gcd(i, j) - 1;
            
            // count > 0인 경우에만 뺄 것이 있음
            if (count > 0) {
                // 격자 내에서 (i, j) 크기의 직사각형 개수 * 대각선 방향 2개
                long long num_rects = (N - i + 1) * (M - j + 1);
                ans -= num_rects * count * 2;
            }
        }
    }

    cout << ans << "\n";

    return 0;
}
