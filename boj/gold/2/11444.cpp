#include <iostream>
#include <vector>

#define ll long long

using namespace std;

const ll MOD = 1000000007;

// 행렬 곱셈 함수
vector<vector<ll>> mul(const vector<vector<ll>>& a, const vector<vector<ll>>& b) {
    vector<vector<ll>> res(2, vector<ll>(2));
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) 
            res[i][j] = (a[i][0] * b[0][j] + a[i][1] * b[1][j]) % MOD;
    }

    return res;
}

// 행렬 거듭제곱 함수
vector<vector<ll>> mat_pow(vector<vector<ll>> base, ll exp) {
    vector<vector<ll>> res = {{1, 0}, {0, 1}}; // 단위 행렬
    while (exp > 0) {
        if (exp % 2 == 1) 
            res = mul(res, base);
        
        base = mul(base, base);
        exp /= 2;
    }

    return res;
}

// 피보나치 수 계산 함수
ll fib(ll n) {
    if (n == 0) return 0;
    vector<vector<ll>> fib_mat = {{1, 1}, {1, 0}};
    vector<vector<ll>> res = mat_pow(fib_mat, n - 1);

    return res[0][0];
}

int main() {
    ll n;
    cin >> n;
    cout << fib(n) << endl;
    
    return 0;
}
