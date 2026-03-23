#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;
const int MAX_N = 805; // N=400, 정점 분할하므로 최대 800+a

struct Edge {
    int to, capacity, flow, rev;
};

vector<Edge> adj[MAX_N];
int level[MAX_N];
int ptr[MAX_N];

// 간선 추가 함수 (정방향 + 역방향)
void addEdge(int from, int to, int cap) {
    adj[from].push_back({to, cap, 0, (int)adj[to].size()});
    adj[to].push_back({from, 0, 0, (int)adj[from].size() - 1});
}

// 레벨 그래프 생성 (BFS)
bool bfs(int s, int t) {
    fill(level, level + MAX_N, -1);
    level[s] = 0;
    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        for (const auto& edge : adj[curr]) {
            if (edge.capacity - edge.flow > 0 && level[edge.to] == -1) {
                level[edge.to] = level[curr] + 1;
                q.push(edge.to);
            }
        }
    }
    return level[t] != -1;
}

// 증가 경로 탐색 및 유량 흘리기 (DFS)
int dfs(int curr, int t, int pushed) {
    if (pushed == 0 || curr == t) return pushed;

    for (int& cid = ptr[curr]; cid < adj[curr].size(); ++cid) {
        auto& edge = adj[curr][cid];
        if (level[curr] + 1 != level[edge.to] || edge.capacity - edge.flow == 0) continue;

        int tr = dfs(edge.to, t, min(pushed, edge.capacity - edge.flow));
        if (tr == 0) continue;

        edge.flow += tr;
        adj[edge.to][edge.rev].flow -= tr;
        return tr;
    }
    return 0;
}

// 디닉 알고리즘 메인
int dinic(int s, int t) {
    int flow = 0;
    while (bfs(s, t)) {
        fill(ptr, ptr + MAX_N, 0);
        while (int pushed = dfs(s, t, INF)) {
            flow += pushed;
        }
    }
    return flow;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, P;
    cin >> N >> P;

    // 1. 정점 분할 간선 연결
    // i_in: i, i_out: i + N
    for (int i = 1; i <= N; ++i) {
        int cap = (i == 1 || i == 2) ? INF : 1; // 1, 2번 도시는 무한, 나머지는 1
        addEdge(i, i + N, cap);
    }

    // 2. 도로 연결
    for (int i = 0; i < P; ++i) {
        int u, v;
        cin >> u >> v;
        // u_out -> v_in, v_out -> u_in (양방향 도로)
        addEdge(u + N, v, 1);
        addEdge(v + N, u, 1);
    }

    // Source: 1_out (N+1), Sink: 2_in (2)
    // 1번 도시에서 출발하여 2번 도시로 들어가는 최대 유량 계산
    cout << dinic(N + 1, 2) << "\n";

    return 0;
}
