#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;
const int MAX_V = 1005;

struct Edge {
    int to, cap, flow, cost, rev;
};

vector<Edge> adj[MAX_V * 2];
int dist[MAX_V * 2], p_node[MAX_V * 2], p_edge[MAX_V * 2];
bool in_q[MAX_V * 2];

void add_edge(int u, int v, int cap, int cost) {
    adj[u].push_back({v, cap, 0, cost, (int)adj[v].size()});
    adj[v].push_back({u, 0, 0, -cost, (int)adj[u].size() - 1});
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int v, e;
    while (cin >> v >> e) {
        // 초기화
        for (int i = 0; i <= v * 2; i++) adj[i].clear();

        // 정점 분할 (Node Splitting)
        // i -> Input Node, i + v -> Output Node
        // 1번 정점과 v번 정점은 경로 2개가 지나가야 하므로 용량 2
        add_edge(1, 1 + v, 2, 0);
        add_edge(v, v + v, 2, 0);

        // 나머지 중간 정점들은 용량 1
        for (int i = 2; i < v; i++) {
            add_edge(i, i + v, 1, 0);
        }

        // 간선 정보 입력
        for (int i = 0; i < e; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            // a의 Output Node -> b의 Input Node
            add_edge(a + v, b, 1, c);
        }

        // MCMF (Source: 1, Sink: v + v)
        // 유량 2를 흘려보내야 함
        int total_flow = 0;
        int total_cost = 0;
        int S = 1, T = v + v;

        while (total_flow < 2) {
            fill(dist, dist + v * 2 + 1, INF);
            fill(in_q, in_q + v * 2 + 1, false);
            fill(p_node, p_node + v * 2 + 1, -1);
            fill(p_edge, p_edge + v * 2 + 1, -1);

            queue<int> q;
            dist[S] = 0;
            in_q[S] = true;
            q.push(S);

            // SPFA (Shortest Path Faster Algorithm)
            while (!q.empty()) {
                int cur = q.front();
                q.pop();
                in_q[cur] = false;

                for (int i = 0; i < adj[cur].size(); i++) {
                    Edge& edge = adj[cur][i];
                    int nxt = edge.to;

                    if (edge.cap - edge.flow > 0 && dist[nxt] > dist[cur] + edge.cost) {
                        dist[nxt] = dist[cur] + edge.cost;
                        p_node[nxt] = cur;
                        p_edge[nxt] = i;
                        if (!in_q[nxt]) {
                            q.push(nxt);
                            in_q[nxt] = true;
                        }
                    }
                }
            }

            // 경로가 없으면 중단 (문제 조건상 항상 경로 존재)
            if (dist[T] == INF) break;

            // 유량 흘리기 (이번 경로는 항상 1만큼 흐름)
            int flow = 1;
            total_flow += flow;
            total_cost += flow * dist[T];

            int cur = T;
            while (cur != S) {
                int prev = p_node[cur];
                int idx = p_edge[cur];
                adj[prev][idx].flow += flow;
                int rev_idx = adj[prev][idx].rev;
                adj[cur][rev_idx].flow -= flow;
                cur = prev;
            }
        }

        cout << total_cost << '\n';
    }

    return 0;
}
