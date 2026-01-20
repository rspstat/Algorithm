#include <iostream>
#include <vector>
#include <map>
#include <numeric>

using namespace std;

typedef long long ll;
const ll MOD = 1000000007;

// 모듈러 역원을 구하기 위한 거듭제곱 함수
ll power(ll base, ll exp) {
    ll res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

// 페르마의 소정리를 이용한 모듈러 역원 (나눗셈 대신 사용)
ll modInverse(ll n) {
    return power(n, MOD - 2);
}

ll gcd(ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

ll lcm(ll a, ll b) {
    if (a == 0 || b == 0) return 0;
    return (a * b) / gcd(a, b);
}

// 파이썬의 addin 함수 역할
void addin(map<pair<int, int>, ll>& lookup, int type, int degree, ll value) {
    lookup[{type, degree}] = (lookup[{type, degree}] + value) % MOD;
}

ll solve() {
    int R, C;
    cin >> R >> C;

    const int type_1_2 = 0;
    const int type_3 = 1;

    // states[4]를 사용하여 슬라이딩 윈도우 방식으로 DP 진행
    vector<map<pair<int, int>, ll>> states(4);
    
    // 초기 상태 설정
    states[0][{type_1_2, 1}] = 1;
    states[0][{type_3, 1}] = 1;

    for (int i = 0; i < R; ++i) {
        int cur = i % 4;
        for (auto const& [state, count] : states[cur]) {
            int prev_type = state.first;
            int degree = state.second;

            if (prev_type == type_1_2) {
                // 3으로 이루어진 2개의 행 추가
                if (i + 2 <= R) {
                    addin(states[(i + 2) % 4], type_3, degree, count);
                }
            } else {
                // 2로 이루어진 1개의 행 추가
                if (i + 1 <= R) {
                    addin(states[(i + 1) % 4], type_1_2, degree, count);
                }
                // 1과 2로 이루어진 2개의 행 추가 (Type 1: 주기 3)
                if (i + 2 <= R) {
                    if (C % 3 == 0) {
                        addin(states[(i + 2) % 4], type_1_2, lcm(degree, 3), (count * 3) % MOD);
                    }
                    if (C % 6 == 0) {
                        addin(states[(i + 2) % 4], type_1_2, lcm(degree, 6), (count * 6) % MOD);
                    }
                }
                // 1과 2로 이루어진 3개의 행 추가 (Type 2: 주기 4)
                if (i + 3 <= R) {
                    if (C % 4 == 0) {
                        addin(states[(i + 3) % 4], type_1_2, lcm(degree, 4), (count * 4) % MOD);
                    }
                }
            }
        }
        states[cur].clear(); // 현재 층 처리가 끝났으므로 비워줌
    }

    ll ans = 0;
    int target = R % 4;
    for (auto const& [state, count] : states[target]) {
        int degree = state.second;
        // (count / degree) % MOD 계산을 위해 역원 곱셈 수행
        ll term = (count * modInverse(degree)) % MOD;
        ans = (ans + term) % MOD;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        cout << "Case #" << t << ": " << solve() << "\n";
    }
    return 0;
}
