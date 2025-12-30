#include <iostream>

using namespace std;

const int MAX = 100001;
int p[MAX];
long long d[MAX];

// Find 함수: 경로 압축과 동시에 루트까지의 가중치 차이(거리) 갱신
int f(int x) {
    if (p[x] == x) return x;
    int rt = f(p[x]);
    d[x] += d[p[x]];
    return p[x] = rt;
}

void u(int a, int b, int w) {
    int ra = f(a);
    int rb = f(b);
    if (ra == rb) return;

    // 벡터 연산: (root_a -> a) + (a -> b) - (root_b -> b) = (root_a -> root_b)
    d[rb] = d[a] + w - d[b];
    p[rb] = ra;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    while (cin >> n >> m && n) {
        for (int i = 1; i <= n; i++) {
            p[i] = i;
            d[i] = 0;
        }

        while (m--) {
            char op;
            int a, b;
            cin >> op >> a >> b;
            if (op == '!') {
                int w;
                cin >> w;
                u(a, b, w);
            } else {
                if (f(a) != f(b)) cout << "UNKNOWN\n";
                else cout << d[b] - d[a] << '\n';
            }
        }
    }

    return 0;
}
