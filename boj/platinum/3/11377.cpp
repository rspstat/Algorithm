#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 1005;

int n, m, k;
vector<int> adj[MAX]; // 직원이 할 수 있는 일 목록
int task_owner[MAX];  // task_owner[j] = j번 일을 담당하는 직원 번호
bool visited[MAX];    // DFS 방문 체크 (일 기준)

// 이분 매칭을 위한 DFS
// cur 직원이 할 수 있는 일을 찾거나, 기존 담당자를 밀어내고 차지할 수 있으면 true
bool dfs(int cur) {
    for (int task : adj[cur]) {
        if (visited[task]) continue;
        visited[task] = true;

        // 일이 비어있거나, 기존 담당자가 다른 일을 할 수 있다면
        if (task_owner[task] == 0 || dfs(task_owner[task])) {
            task_owner[task] = cur;
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> k;

    for (int i = 1; i <= n; i++) {
        int cnt;
        cin >> cnt;
        while (cnt--) {
            int work;
            cin >> work;
            adj[i].push_back(work);
        }
    }

    int ans = 0;

    // 1. 모든 직원에 대해 첫 번째 일 매칭 시도
    for (int i = 1; i <= n; i++) {
        fill(visited, visited + MAX, false);
        if (dfs(i)) ans++;
    }

    // 2. 모든 직원에 대해 두 번째 일 매칭 시도 (최대 K번 성공 가능)
    // 한 직원은 최대 2개의 일을 할 수 있다는 조건이 여기서 자연스럽게 해결됨
    // (위에서 한 번, 여기서 한 번 총 2번의 기회)
    for (int i = 1; i <= n; i++) {
        if (k == 0) break; // K번의 추가 기회를 모두 소진하면 종료
        
        fill(visited, visited + MAX, false);
        if (dfs(i)) {
            ans++;
            k--;
        }
    }

    cout << ans;

    return 0;
}
