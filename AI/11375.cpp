#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 1005; // N, M이 최대 1000이므로 넉넉하게 잡음

int N, M;
vector<int> adj[MAX]; // adj[i]: i번 직원이 할 수 있는 일들의 목록
int occupied[MAX];    // occupied[j]: j번 일을 현재 누가 담당하고 있는지 저장 (0이면 없음)
bool visited[MAX];    // visited[j]: 이번 매칭 시도에서 j번 일을 확인했는지 여부

// DFS를 통해 직원을 일에 매칭시키는 함수
bool dfs(int cur_employee) {
    // 현재 직원이 할 수 있는 일들을 순회
    for (int task : adj[cur_employee]) {
        // 이번 시도에서 이미 확인한 일이라면 패스 (무한 루프 방지)
        if (visited[task]) continue;
        
        visited[task] = true;

        // 1. 해당 일이 비어있거나 (occupied[task] == 0)
        // 2. 그 일을 하고 있는 사람(occupied[task])이 다른 일로 옮길 수 있다면 (dfs 재귀)
        if (occupied[task] == 0 || dfs(occupied[task])) {
            occupied[task] = cur_employee; // 현재 직원이 그 일을 맡음
            return true;
        }
    }
    return false; // 매칭 실패
}

int main() {
    // 입출력 속도 향상
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;

    for (int i = 1; i <= N; ++i) {
        int cnt;
        cin >> cnt; // 각 직원이 할 수 있는 일의 개수
        while (cnt--) {
            int task;
            cin >> task;
            adj[i].push_back(task);
        }
    }

    int match_count = 0;
    
    // 1번 직원부터 N번 직원까지 순서대로 매칭 시도
    for (int i = 1; i <= N; ++i) {
        // 매번 시도할 때마다 visited 배열 초기화
        fill(visited, visited + MAX, false);
        
        // 매칭에 성공하면 카운트 증가
        if (dfs(i)) {
            match_count++;
        }
    }

    cout << match_count << "\n";

    return 0;
}
