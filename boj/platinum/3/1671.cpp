#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Shark {
    int sz, sp, iq;
};

int N;
vector<Shark> sharks;
vector<int> adj[51];
int matched[51];
bool visited[51];

// 상어 A가 상어 B를 먹을 수 있는지 확인하는 함수
bool can_eat(int a, int b) {
    if (sharks[a].sz == sharks[b].sz && sharks[a].sp == sharks[b].sp && sharks[a].iq == sharks[b].iq) {
        // 능력치가 모두 같다면 인덱스가 작은 상어가 먹는 것으로 규칙을 정함
        return a < b;
    }
    return sharks[a].sz >= sharks[b].sz && sharks[a].sp >= sharks[b].sp && sharks[a].iq >= sharks[b].iq;
}

// 이분 매칭을 위한 DFS 함수
bool dfs(int cur) {
    for (int next : adj[cur]) {
        if (visited[next]) continue;
        visited[next] = true;

        // 해당 피식자 상어가 아직 안 먹혔거나, 
        // 기존에 먹었던 상어가 다른 상어를 먹으러 이동할 수 있다면 매칭 성공
        if (matched[next] == -1 || dfs(matched[next])) {
            matched[next] = cur;
            return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    sharks.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> sharks[i].sz >> sharks[i].sp >> sharks[i].iq;
    }

    // 먹을 수 있는 관계를 그래프로 구성
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) continue;
            if (can_eat(i, j)) {
                adj[i].push_back(j);
            }
        }
    }

    int total_matches = 0;
    fill(matched, matched + N, -1);

    // 각 상어는 최대 2마리까지 먹을 수 있음
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 2; j++) {
            fill(visited, visited + N, false);
            if (dfs(i)) {
                total_matches++;
            }
        }
    }

    // 살아남은 상어 = 전체 상어 - 먹힌 상어 수
    cout << N - total_matches << "\n";

    return 0;
}
