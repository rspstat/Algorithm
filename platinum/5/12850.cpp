#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
const int MOD = 1'000'000'007;
const int SZ = 8;

using Mat = array<array<int, SZ>, SZ>;

Mat mul(const Mat& A, const Mat& B) {
    Mat C{};
    for (int i = 0; i < SZ; ++i) {
        for (int k = 0; k < SZ; ++k) {
            if (!A[i][k]) continue;
            long long aik = A[i][k];
            for (int j = 0; j < SZ; ++j) {
                C[i][j] = (C[i][j] + aik * B[k][j]) % MOD;
            }
        }
    }
    return C;
}

Mat mpow(Mat base, long long exp) {
    Mat res{};
    for (int i = 0; i < SZ; ++i) res[i][i] = 1; // identity
    while (exp > 0) {
        if (exp & 1) res = mul(res, base);
        base = mul(base, base);
        exp >>= 1;
    }
    return res;
}

void solve() {
    long long n; 
    cin >> n;

    // Adjacency for 본대 산책 그래프 (0..7)
    Mat A{};
    auto link = [&](int u, int v) {
        A[u][v] = (A[u][v] + 1) % MOD;
        A[v][u] = (A[v][u] + 1) % MOD;
    };
    link(0,1); link(0,2);
    link(1,2); link(1,3);
    link(2,3); link(2,4);
    link(3,4); link(3,5);
    link(4,5); link(4,7);
    link(5,6);
    link(6,7);

    // walks of length n from 0 to 0 == (A^n)[0][0]
    Mat An = mpow(A, n);
    cout << An[0][0] % MOD << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
