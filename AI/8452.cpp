#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;
int n, m, q;

// 간선 정보 저장 (u, v)
vector<pair<int, int>> all_edges;
// 인접 리스트
vector<int> adj[1001];
// 쿼리 저장
struct Query {
    char type;
    int val;
};
vector<Query> queries;
// 해당 간선이 쿼리에 의해 삭제되는지 여부
bool is_deleted[100001]; 
// 최단 거리 배열
int dist[1001];
// 정답 저장용
vector<int> results;

void bfs_update(int start_node) {
    queue<int> q;
    // 갱신이 필요한 노드만 큐에 넣음
    // start_node는 이미 거리가 갱신되었다고 가정하고 큐에 넣거나,
    // 호출하기 전에 조건을 체크하고 넣음.
    // 여기서는 단순히 큐에 넣고 시작
    q.push(start_node);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            // 거리가 단축되는 경우에만 갱신 및 큐 추가
            if (dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> q;

    // 간선 입력 (1-based index를 맞추기 위해 더미 데이터 0번 추가)
    all_edges.push_back({0, 0});
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        all_edges.push_back({u, v});
    }

    // 쿼리 입력
    for (int i = 0; i < q; i++) {
        char t;
        int p;
        cin >> t >> p;
        queries.push_back({t, p});
        if (t == 'U') {
            is_deleted[p] = true; // 삭제될 간선 표시
        }
    }

    // 1. 초기 그래프 구성 (삭제되지 않은 간선만 추가)
    for (int i = 1; i <= m; i++) {
        if (!is_deleted[i]) {
            adj[all_edges[i].first].push_back(all_edges[i].second);
        }
    }

    // 2. 초기 최단 거리 계산 (BFS)
    fill(dist, dist + n + 1, INF);
    dist[1] = 0;
    
    queue<int> q_bfs;
    q_bfs.push(1);
    
    while(!q_bfs.empty()){
        int u = q_bfs.front();
        q_bfs.pop();
        for(int v : adj[u]){
            if(dist[v] == INF){
                dist[v] = dist[u] + 1;
                q_bfs.push(v);
            }
        }
    }

    // 3. 쿼리 역순 처리
    for (int i = q - 1; i >= 0; i--) {
        char type = queries[i].type;
        int val = queries[i].val;

        if (type == 'E') {
            // 현재 거리 저장
            if (dist[val] == INF) results.push_back(-1);
            else results.push_back(dist[val]);
        } else {
            // 간선 복구 (추가)
            int u = all_edges[val].first;
            int v = all_edges[val].second;
            
            adj[u].push_back(v);
            
            // 간선이 추가되어 거리가 단축될 수 있다면 BFS 전파
            // u까지 도달 불가능하면 v도 갱신 안됨
            if (dist[u] != INF && dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                bfs_update(v);
            }
        }
    }

    // 결과 출력 (역순으로 저장했으므로 다시 뒤집어서 출력)
    reverse(results.begin(), results.end());
    for (int res : results) {
        cout << res << "\n";
    }

    return 0;
}
