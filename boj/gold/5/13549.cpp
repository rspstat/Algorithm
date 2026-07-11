#include <bits/stdc++.h>
using namespace std;

int n, k;

void solve() {
    cin >> n >> k;
    const int MAXX = 100000;
    const int INF = 1e9;

    vector<int> dist(MAXX + 1, INF);
    deque<int> dq;

    dist[n] = 0;
    dq.push_back(n);

    while (!dq.empty()) {
        int x = dq.front(); dq.pop_front();
        if (x == k) break;

        // 0초 이동: 순간이동 x -> 2*x
        long long nx = 1LL * x * 2;
        if (nx <= MAXX && dist[nx] > dist[x]) {
            dist[nx] = dist[x];
            dq.push_front((int)nx);
        }
        // 1초 이동: x-1
        if (x - 1 >= 0 && dist[x - 1] > dist[x] + 1) {
            dist[x - 1] = dist[x] + 1;
            dq.push_back(x - 1);
        }
        // 1초 이동: x+1
        if (x + 1 <= MAXX && dist[x + 1] > dist[x] + 1) {
            dist[x + 1] = dist[x] + 1;
            dq.push_back(x + 1);
        }
    }

    cout << dist[k] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
