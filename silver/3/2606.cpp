#include <iostream>
#include <vector>

#define MAX 101

using namespace std;

int n = 0; int m = 0;   // n = 컴퓨터의 수(vertex), m = edge의 수 
vector<int> graph[MAX]; // 네트워크 연결 상태를 나타내는 인접리스트
bool visited[MAX] = {false, };  // 방문 여부를 나타내는 배열
int res = 0; // 웜 바이러스에 걸리게 되는 컴퓨터의 수

void search(int node) {
    for (int i = 0; i < graph[node].size(); i++) {
        int cur = graph[node][i];

        if (visited[cur] == 0) {
            visited[cur] = true;
            res++;
            search(cur);
        }
    }
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    // 1번 컴퓨터부터 탐색
    visited[1] = true;
    search(1);

    cout << res << endl;
    return 0;
}


