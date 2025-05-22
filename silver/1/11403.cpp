#include <iostream>

using namespace std;

int graph[101][101];

// 플로이드-워셜 알고리즘 이용

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N = 0;
    cin >> N;

    // 그래프를 입력 받음
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> graph[i][j];
        }
    }

    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (graph[i][k] && graph[k][j]) {
                    graph[i][j] = 1;
                }
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << graph[i][j] << " ";
        }

        cout << endl;
    }

    return 0;
}
