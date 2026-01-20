#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;
const int MAX_V = 205; // Source(1) + Sink(1) + N(100) + M(100)

struct Edge {
    int to, capacity, flow, cost, rev;
};

vector<Edge> adj[MAX_V];
int dist[MAX_V];
bool inQueue[MAX_V];
int parent[MAX_V];
int edgeIdx[MAX_V];

// 간선 추가 함수 (정방향: cost, 역방향: -cost)
void addEdge(int u, int v, int cap, int cost) {
    adj[u].push_back({v, cap, 0, cost, (int)adj[v].size()});
    adj[v].push_back({u, 0, 0, -cost, (int)adj[u].size() - 1});
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;

    // 노드 번호 매핑
    // Source: 0
    // Sink: N + M + 1
    // 사람: 1 ~ N
    // 서점: N + 1 ~ N + M
    int S = 0;
    int T = N + M + 1;

    // 1. 사람 -> Sink (용량: 필요량, 비용: 0)
    for (int i = 1; i <= N; ++i) {
        int need;
        cin >> need;
        addEdge(i, T, need, 0);
    }

    // 2. Source -> 서점 (용량: 보유량, 비용: 0)
    for (int i = 1; i <= M; ++i) {
        int stock;
        cin >> stock;
        addEdge(S, N + i, stock, 0);
    }

    // 3. 서점 -> 사람 (용량: 무한, 비용: 배송비)
    // 입력 순서: 서점 1에서 사람 1~N, 서점 2에서 사람 1~N ...
    for (int j = 1; j <= M; ++j) {
        for (int i = 1; i <= N; ++i) {
            int cost;
            cin >> cost;
            // 서점(N+j) -> 사람(i)
            addEdge(N + j, i, INF, cost);
        }
    }

    int total_cost = 0;

    // MCMF (SPFA Algorithm)
    while (true) {
        fill(dist, dist + MAX_V, INF);
        fill(inQueue, inQueue + MAX_V, false);
        fill(parent, parent + MAX_V, -1);
        fill(edgeIdx, edgeIdx + MAX_V, -1);

        queue<int> q;
        dist[S] = 0;
        inQueue[S] = true;
        q.push(S);

        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            inQueue[curr] = false;

            for (int i = 0; i < adj[curr].size(); ++i) {
                Edge& e = adj[curr][i];
                int next = e.to;

                // 잔여 용량이 있고, 더 적은 비용으로 갈 수 있다면 갱신
                if (e.capacity - e.flow > 0 && dist[next] > dist[curr] + e.cost) {
                    dist[next] = dist[curr] + e.cost;
                    parent[next] = curr;
                    edgeIdx[next] = i;

                    if (!inQueue[next]) {
                        q.push(next);
                        inQueue[next] = true;
                    }
                }
            }
        }

        // Sink까지 가는 경로가 없으면 종료
        if (parent[T] == -1) break;

        // 찾은 경로에서 흘릴 수 있는 최대 유량(bottleneck) 계산
        int flow = INF;
        for (int i = T; i != S; i = parent[i]) {
            int prev = parent[i];
            int idx = edgeIdx[i];
            flow = min(flow, adj[prev][idx].capacity - adj[prev][idx].flow);
        }

        // 유량 흘리기 및 비용 계산
        for (int i = T; i != S; i = parent[i]) {
            int prev = parent[i];
            int idx = edgeIdx[i];
            
            adj[prev][idx].flow += flow;
            int revIdx = adj[prev][idx].rev;
            adj[i][revIdx].flow -= flow;

            total_cost += flow * adj[prev][idx].cost;
        }
    }

    cout << total_cost << "\n";

    return 0;
}
