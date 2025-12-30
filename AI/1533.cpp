#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MOD = 1000003;

struct Mat {
    int sz;
    vector<vector<long long>> d;
    Mat(int n) : sz(n), d(n, vector<long long>(n, 0)) {}
    
    Mat operator*(const Mat& o) const {
        Mat res(sz);
        for (int i = 0; i < sz; i++) {
            for (int k = 0; k < sz; k++) {
                if (!d[i][k]) continue;
                for (int j = 0; j < sz; j++) {
                    res.d[i][j] = (res.d[i][j] + d[i][k] * o.d[k][j]) % MOD;
                }
            }
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    long long n, s, e, t;
    cin >> n >> s >> e >> t;
    s--; e--;

    // 정점을 5개로 분할하여 가중치 처리 (N*5)
    Mat m(n * 5);

    for (int i = 0; i < n; i++) {
        for (int j = 1; j < 5; j++) {
            // 내부 간선: 시간 지연을 위한 노드 연결 (k -> k-1)
            m.d[i * 5 + j][i * 5 + j - 1] = 1;
        }
    }

    for (int i = 0; i < n; i++) {
        string str;
        cin >> str;
        for (int j = 0; j < n; j++) {
            int w = str[j] - '0';
            if (w > 0) {
                // 시작점의 0번 상태에서 도착점의 w-1번 상태로 연결
                m.d[i * 5][j * 5 + w - 1] = 1;
            }
        }
    }

    Mat ans(n * 5);
    for (int i = 0; i < n * 5; i++) ans.d[i][i] = 1;

    while (t) {
        if (t & 1) ans = ans * m;
        m = m * m;
        t >>= 1;
    }

    cout << ans.d[s * 5][e * 5];

    return 0;
}
