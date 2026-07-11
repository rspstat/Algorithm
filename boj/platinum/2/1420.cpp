#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

const int INF = 1e9;
const int MAX_N = 100;
// 정점은 최대 100*100*2 개
const int MAX_V = 20005;

struct Edge {
    int to, cap, flow, rev;
};

int n, m;
char grid[MAX_N][MAX_N];
vector<Edge> adj[MAX_V];
int level[MAX_V], work[MAX_V];

// 간선 추가 함수 (유량 그래프)
void add_edge(int u, int v, int cap) {
    adj[u].push_back({v, cap, 0, (int)adj[v].size()});
    adj[v].push_back({u, 0, 0, (int)adj[u].size() - 1});
}

// 2차원 좌표 -> 1차원 In 노드 번호 변환
int get_in(int r, int c) {
    return (r * m + c) * 2;
}

// 2차원 좌표 -> 1차원 Out 노드 번호 변환
int get_out(int r, int c) {
    return (r * m + c) * 2 + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;

    int start_node = -1, end_node = -1;
    int k_r, k_c, h_r, h_c;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            grid[i][j] = s[j];
            if (grid[i][j] == 'K') {
                k_r = i; k_c = j;
                start_node = get_in(i, j); // 시작은 K의 In (K->K_out->...)
            } else if (grid[i][j] == 'H') {
                h_r = i; h_c = j;
                end_node = get_in(i, j);   // 도착은 H의 In
            }
        }
    }

    // 예외 처리: K와 H가 붙어있는 경우
    if (abs(k_r - h_r) + abs(k_c - h_c) == 1) {
        cout << -1;
        return 0;
    }

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '#') continue;

            int u_in = get_in(i, j);
            int u_out = get_out(i, j);

            // 1. 정점 분할 (In -> Out)
            int cap = 1;
            // K와 H는 벽을 세울 수 없으므로 무한대 용량
            if (grid[i][j] == 'K' || grid[i][j] == 'H') cap = INF;
            add_edge(u_in, u_out, cap);

            // 2. 인접한 칸 연결 (Out -> Next In)
            for (int d = 0; d < 4; d++) {
                int ni = i + dx[d];
                int nj = j + dy[d];

                if (ni >= 0 && ni < n && nj >= 0 && nj < m && grid[ni][nj] != '#') {
                    int v_in = get_in(ni, nj);
                    // 이동 자체는 제한이 없음 (무한대)
                    add_edge(u_out, v_in, INF);
                }
            }
        }
    }

    // 최대 유량 구하기 (Edmonds-Karp 방식: BFS 반복)
    // 정답이 작으므로(최대 4) 복잡한 Dinic 대신 간단한 BFS로 충분
    int total_flow = 0;
    int S = get_in(k_r, k_c); // Start (실제 흐름: K_in -> K_out -> ...)
    int T = get_in(h_r, h_c); // Sink

    while (true) {
        vector<int> parent(MAX_V, -1);
        vector<int> edge_idx(MAX_V, -1);
        queue<int> q;

        parent[S] = S;
        q.push(S);

        while (!q.empty() && parent[T] == -1) {
            int cur = q.front();
            q.pop();

            for (int i = 0; i < adj[cur].size(); i++) {
                int nxt = adj[cur][i].to;
                if (adj[cur][i].cap - adj[cur][i].flow > 0 && parent[nxt] == -1) {
                    parent[nxt] = cur;
                    edge_idx[nxt] = i;
                    q.push(nxt);
                }
            }
        }

        if (parent[T] == -1) break;

        int flow = INF;
        for (int i = T; i != S; i = parent[i]) {
            int prev = parent[i];
            int idx = edge_idx[i];
            flow = min(flow, adj[prev][idx].cap - adj[prev][idx].flow);
        }

        for (int i = T; i != S; i = parent[i]) {
            int prev = parent[i];
            int idx = edge_idx[i];
            adj[prev][idx].flow += flow;
            int rev_idx = adj[prev][idx].rev;
            adj[i][rev_idx].flow -= flow;
        }

        total_flow += flow;
    }

    cout << total_flow;

    return 0;
}
