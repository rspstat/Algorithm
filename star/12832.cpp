#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    if (!(cin >> N >> M)) return 0;

    vector<vector<pair<int, int>>> requests(N + 1);
    for (int i = 1; i <= M; i++) {
        int u, v;
        cin >> u >> v;
        requests[u].push_back({v, i});
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<pair<int, int>> ans;

    for (int i = 1; i <= N; i++) {
        for (auto& req : requests[i]) {
            pq.push(req);
        }

        while (!pq.empty() && pq.top().first < i) {
            pq.pop();
        }

        if (!pq.empty()) {
            ans.push_back({i, pq.top().second});
            pq.pop();
        }
    }

    cout << ans.size() << "\n";
    for (const auto& p : ans) {
        cout << p.first << " " << p.second << "\n";
    }

    return 0;
}
