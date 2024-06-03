#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>

using namespace std;

int arr[1001][1001];
int visited[1001];    //방문한 노드 배열
int n, m, v_start;    //vertex 개수, edge 개수, vertex 시작 번호

void dfs(int v_start) {     //깊이 우선 탐색, depth-first-search
    visited[v_start] = 1;  
    cout << v_start << " "; 

    for (int i = 1; i <= n; i++) {
        if ( arr[v_start][i] == 1 && visited[i] == 0 ) 
            dfs(i);     //재귀, dfs, O(n^2)

        if ( i == n )
            return;
    }
}

void bfs(int v_start) {     //너비 우선 탐색, breath-first-search
    int next;       //클래스 오류 떠서 선언 해야함;;
    queue<int> q;
    q.push(v_start);

    while (!q.empty()) {
        next = q.front();
        visited[next] = 1;
        cout << next << " ";
        q.pop();

        for (int i = 1; i <= n; i++) {
            if (arr[next][i] == 1 && visited[i] == 0) {
                q.push(i);
                visited[i] = 1;
            }
        }
    }
}   //얘도 O(n^2)

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int u, v;   //edge, vertex, 간선, 정점

    cin >> n >> m >> v_start;

    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        arr[u][v] = 1;
        arr[v][u] = 1;
    }

    dfs(v_start);

    cout << "\n";

    memset(visited, 0, sizeof(visited));    //dfs 초기화, string.h -> memset

    bfs(v_start);

    return 0;   
}   
