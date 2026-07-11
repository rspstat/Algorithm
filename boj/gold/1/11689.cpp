#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long n;
    std::cin >> n;

    long long result = n; // 오일러 피 함수 결과값 (초기값 = n)

    // n의 소인수를 찾기 위해 2부터 n의 제곱근까지 반복
    for (long long p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            // p가 소인수인 경우, 오일러 피 함수 공식 적용
            // result = result * (1 - 1/p)
            result = result / p * (p - 1);

            // n에서 소인수 p를 모두 제거
            while (n % p == 0) {
                n /= p;
            }
        }
    }

    // 위 반복문 후 n이 1보다 크면, 그 자체가 마지막 소인수
    if (n > 1) {
        result = result / n * (n - 1);
    }

    std::cout << result << "\n";

    return 0;
}
