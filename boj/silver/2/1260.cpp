#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>

using namespace std;

int arr[1001][1001];  // 그래프를 표현하는 인접 행렬
int visit[1001];    // 방문한 노드를 기록하는 배열
int n, m, v_num;    // 정점의 개수, 간선의 개수, 시작 정점 번호

void dfs(int v_num) {     // 깊이 우선 탐색, depth-first-search
    visit[v_num] = 1;   // 시작 정점을 방문했음 -> 1
    cout << v_num << " "; // 현재 정점을 출력

    // 현재 정점에 인접한 모든 정점을 탐색
    for (int i = 1; i <= n; i++) {
        if (arr[v_num][i] == 1 && visit[i] == 0) {    // 방문 안했으면,
            dfs(i); // 재귀적으로 DFS 수행
        }

        // 모든 정점을 처리하면 재귀를 종료
        if (i == n)
            return;
    }
}

void bfs(int v_num) {     // 너비 우선 탐색 함수, breath-first-search
    int next;       // 다음에 탐색할 정점
    queue<int> q;   // BFS를 위한 큐
    q.push(v_num); // 시작 정점을 큐에 추가

    while (!q.empty()) {
        next = q.front(); // 큐의 가장 앞에 있는 정점을 가져옴
        visit[next] = 1; // 해당 정점을 방문했다고 표시
        cout << next << " "; // 현재 정점을 출력
        q.pop(); // 큐에서 정점을 제거

        // 현재 정점에 인접한 모든 정점을 탐색
        for (int i = 1; i <= n; i++) {
            if (arr[next][i] == 1 && visit[i] == 0) { // 방문 안했으면
                q.push(i);  // 인접 정점을 큐에 추가
                visit[i] = 1; // 큐에 추가한 정점을 방문했다고 표시
            }
        }
    }
}   

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int u, v;   // 간선의 양 끝 정점

    cin >> n >> m >> v_num; // 정점의 개수, 간선의 개수, 시작 정점 입력

    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        arr[u][v] = 1; // 양방향 간선을 인접 행렬에 표시
        arr[v][u] = 1;
    }

    dfs(v_num); // DFS 수행

    cout << "\n";

    memset(visit, 0, sizeof(visit)); // 방문 배열 초기화

    bfs(v_num); // BFS 수행

    return 0;   
}   
