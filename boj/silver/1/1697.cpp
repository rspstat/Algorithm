#include <iostream>
#include <queue>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int start, target;

    cin >> start >> target;

    queue<int> q;
    int visited[100001] = {0}; // 각 위치까지 걸리는 최소 시간 저장
    int cur_pos;    // 현재 위치

    q.push(start);  // 수빈이 처음 위치 push

    while (!q.empty()) {
        cur_pos = q.front();    // 현재 포지션에 큐 앞 할당
        q.pop();    // 할당하고 삭제

        // 범위를 벗어나면 무시
        if (cur_pos < 0 || cur_pos > 100000) 
            continue;

        // 목표 위치에 도달하면 출력 후 종료
        if (cur_pos == target) {   
            cout << visited[cur_pos];
            break;
        }

        // 포지션 변경 3가지
        int next_pos[3] = {
            cur_pos - 1,
            cur_pos + 1,
            cur_pos * 2
        };

        // 현재 위치에서 포지션 변경 3가지 전부 시전
        for (int i = 0; i < 3; i++) {      
            int next = next_pos[i];

            // 1. 범위를 벗어나지 않고, 2. 아직 방문하지 않은 위치인 경우
            if (next >= 0 && next <= 100000 && visited[next] == 0) {   
                visited[next] = visited[cur_pos] + 1;   // 현재까지 걸린 시간 1초 추가
                q.push(next);   // 다음 위치를 큐에 추가하여 계속
            }
        }
    }

    return 0;
}
