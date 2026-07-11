#include <iostream>

using namespace std;

const int INF = 10000000; // 충분히 큰 값
int dist[101][101];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, M;
    cin >> N >> M;

    // 거리 배열 초기화
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (i == j) 
                dist[i][j] = 0;
            else 
                dist[i][j] = INF;
        }
    }

    // 친구 관계 입력
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        dist[a][b] = 1;
        dist[b][a] = 1;
    }

    // 플로이드 워셜 (중간점 k를 거쳐 가는 거리)
    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (dist[i][j] > dist[i][k] + dist[k][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    int ans = 0;
    int min_sum = INF * 100;

    // 각 사람마다 거리 합 계산
    for (int i = 1; i <= N; i++) {
        int sum = 0;
        for (int j = 1; j <= N; j++) {
            sum += dist[i][j];
        }

        if (sum < min_sum) {
            min_sum = sum;
            ans = i;
        }
    }

    cout << ans << '\n';
    return 0;
}

// bfs ver
// #include <iostream>
// #include <vector>
// #include <queue>
// #include <climits>
// using namespace std;

// int N, M;
// vector<int> graph[101];

// int bfs(int start) {
//     vector<int> dist(N + 1, -1); // 방문하지 않은 곳은 -1
//     queue<int> q;

//     q.push(start);
//     dist[start] = 0;

//     while (!q.empty()) {
//         int cur = q.front();
//         q.pop();

//         for (int next : graph[cur]) {
//             if (dist[next] == -1) {
//                 dist[next] = dist[cur] + 1;
//                 q.push(next);
//             }
//         }
//     }

//     int sum = 0;
//     for (int i = 1; i <= N; i++) {
//         sum += dist[i];
//     }
//     return sum;
// }

// int main() {
//     cin >> N >> M;

//     // 친구 관계 입력 (양방향)
//     for (int i = 0; i < M; i++) {
//         int a, b;
//         cin >> a >> b;
//         graph[a].push_back(b);
//         graph[b].push_back(a);
//     }

//     int min_bacon = INT_MAX;
//     int ans = 0;

//     for (int i = 1; i <= N; i++) {
//         int bacon = bfs(i);
//         if (bacon < min_bacon) {
//             min_bacon = bacon;
//             ans = i;
//         }
//     }

//     cout << ans << '\n';
//     return 0;
// }

