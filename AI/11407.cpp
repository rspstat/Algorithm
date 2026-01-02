#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;
const int MAX_V = 205; // N, M <= 100 이므로 정점은 약 202개

struct Edge {
    int to, cap, flow, cost, rev;
};

vector<Edge> adj[MAX_V];
int dist[MAX_V], p_node[MAX_V], p_edge[MAX_V];
bool in_q[MAX_V];

// 간선 추가 함수
void add_edge(int u, int v, int cap, int cost) {
    adj[u].push_back({v, cap, 0, cost, (int)adj[v].size()});
    adj[v].push_back({u, 0, 0, -cost, (int)adj[u].size() - 1});
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    int S = 0;
    int T = n + m + 1;

    // 1. 사람들의 수요량 입력 (사람 -> Sink)
    // 사람은 m + 1 ~ m + n 번 노드 사용
    for (int i = 1; i <= n; i++) {
        int capacity;
        cin >> capacity;
        add_edge(m + i, T, capacity, 0);
    }

    // 2. 서점의 보유량 입력 (Source -> 서점)
    // 서점은 1 ~ m 번 노드 사용
    for (int i = 1; i <= m; i++) {
        int capacity;
        cin >> capacity;
        add_edge(S, i, capacity, 0);
    }

    // 서점별 사람에게 판매 가능한 용량 임시 저장
    vector<vector<int>> capacities(m + 1, vector<int>(n + 1));
    for (int j = 1; j <= m; j++) {
        for (int i = 1; i <= n; i++) {
            cin >> capacities[j][i];
        }
    }

    // 3. 서점 -> 사람 간선 연결 (비용 포함)
    for (int j = 1; j <= m; j++) {
        for (int i = 1; i <= n; i++) {
            int cost;
            cin >> cost;
            // 서점 j -> 사람 i
            // 용량: capacities[j][i], 비용: cost
            add_edge(j, m + i, capacities[j][i], cost);
        }
    }

    int total_flow = 0;
    int total_cost = 0;

    // MCMF 수행 (SPFA)
    while (true) {
        fill(dist, dist + MAX_V, INF);
        fill(in_q, in_q + MAX_V, false);
        fill(p_node, p_node + MAX_V, -1);
        fill(p_edge, p_edge + MAX_V, -1);

        queue<int> q;
        dist[S] = 0;
        in_q[S] = true;
        q.push(S);

        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            in_q[cur] = false;

            for (int i = 0; i < adj[cur].size(); i++) {
                Edge& e = adj[cur][i];
                int nxt = e.to;

                if (e.cap - e.flow > 0 && dist[nxt] > dist[cur] + e.cost) {
                    dist[nxt] = dist[cur] + e.cost;
                    p_node[nxt] = cur;
                    p_edge[nxt] = i;
                    if (!in_q[nxt]) {
                        q.push(nxt);
                        in_q[nxt] = true;
                    }
                }
            }
        }

        if (dist[T] == INF) break;

        int flow = INF;
        int cur = T;
        while (cur != S) {
            int prev = p_node[cur];
            int idx = p_edge[cur];
            flow = min(flow, adj[prev][idx].cap - adj[prev][idx].flow);
            cur = prev;
        }

        cur = T;
        while (cur != S) {
            int prev = p_node[cur];
            int idx = p_edge[cur];
            adj[prev][idx].flow += flow;
            int rev_idx = adj[prev][idx].rev;
            adj[cur][rev_idx].flow -= flow;
            cur = prev;
        }

        total_flow += flow;
        total_cost += flow * dist[T];
    }

    cout << total_flow << '\n' << total_cost;

    return 0;
}
