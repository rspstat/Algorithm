#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;
const int MAX_V = 805; // N, M <= 400 이므로 소스, 싱크 포함 802개 이상 필요

struct Edge {
    int to, cap, flow, cost, rev;
};

vector<Edge> adj[MAX_V];
int dist[MAX_V], p_node[MAX_V], p_edge[MAX_V];
bool in_q[MAX_V];

// 간선 추가 (정방향: 비용 w, 역방향: 비용 -w)
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

    // 1. 소스 -> 직원 연결
    for (int i = 1; i <= n; i++) {
        add_edge(S, i, 1, 0);
        
        int k;
        cin >> k;
        while (k--) {
            int job, wage;
            cin >> job >> wage;
            // 2. 직원 -> 일 연결 (일 번호는 N + job 으로 매핑)
            add_edge(i, n + job, 1, wage);
        }
    }

    // 3. 일 -> 싱크 연결
    for (int i = 1; i <= m; i++) {
        add_edge(n + i, T, 1, 0);
    }

    int total_flow = 0;
    int total_cost = 0;

    // MCMF (SPFA 알고리즘)
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

                // 잔여 용량이 있고, 더 저렴한 경로라면 갱신
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

        // 더 이상 싱크로 가는 경로가 없으면 종료
        if (dist[T] == INF) break;

        // 이 문제에서는 모든 용량이 1이므로 흐르는 유량은 항상 1
        int flow = 1; 
        
        // 경로 추적하며 유량 갱신
        int cur = T;
        while (cur != S) {
            int prev = p_node[cur];
            int idx = p_edge[cur];
            
            adj[prev][idx].flow += flow;
            int rev_idx = adj[prev][idx].rev;
            adj[cur][rev_idx].flow -= flow;
            
            cur = prev;
        }

        total_flow += flow;
        total_cost += dist[T];
    }

    cout << total_flow << '\n' << total_cost;

    return 0;
}
