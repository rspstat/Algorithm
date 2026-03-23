#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;

struct Edge {
    int to, weight;
};

struct Node {
    int curr, cost, count;
    bool operator>(const Node& other) const {
        return cost > other.cost;
    }
};

int N, M, K, S, D;
vector<Edge> adj[1001];
int dist[1001][1001]; // dist[노드][간선개수]

void dijkstra() {
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= N; j++) dist[i][j] = INF;
    }

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    dist[S][0] = 0;
    pq.push({S, 0, 0});

    while (!pq.empty()) {
        Node top = pq.top();
        pq.pop();

        int curr = top.curr;
        int cost = top.cost;
        int count = top.count;

        if (cost > dist[curr][count]) continue;
        if (count >= N - 1) continue;

        // 최적화: 더 적은 간선으로 이미 더 싸게 도착했다면 무시
        bool skip = false;
        for (int i = 0; i < count; i++) {
            if (dist[curr][i] <= cost) {
                skip = true;
                break;
            }
        }
        if (skip) continue;

        for (auto& edge : adj[curr]) {
            int next = edge.to;
            int next_cost = cost + edge.weight;
            int next_count = count + 1;

            if (dist[next][next_count] > next_cost) {
                dist[next][next_count] = next_cost;
                pq.push({next, next_cost, next_count});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> K >> S >> D;
    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    dijkstra();

    vector<int> taxes(K + 1, 0);
    for (int i = 1; i <= K; i++) cin >> taxes[i];

    int total_tax = 0;
    for (int i = 0; i <= K; i++) {
        total_tax += taxes[i];
        int min_val = INF;
        for (int cnt = 1; cnt < N; cnt++) {
            if (dist[D][cnt] == INF) continue;
            min_val = min(min_val, dist[D][cnt] + cnt * total_tax);
        }
        cout << min_val << "\n";
    }

    return 0;
}
