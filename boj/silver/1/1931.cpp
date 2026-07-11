#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> meets(n);

    for (int i = 0; i < n; i++) {
        int start, end;
        cin >> start >> end;

        meets[i] = {end, start};    // meets 벡터에 종료시간, 시작시간 저장
    }

    sort(meets.begin(), meets.end());

    int cnt = 0;
    int let = 0; // last_end_time

    // 회의 하나씩 선택하여 카운트
    for (const auto& meet : meets) {  
        int end = meet.first;
        int start = meet.second;

        if (start >= let) { // 이전 회의 종료 이후에 시작하는 회의만 선택
            cnt++;          
            let = end;      // 현재 회의의 종료 시간 업데이트
        }
    }

    cout << cnt << endl;

    return 0;
}

// 문제 접근 방법
// 1. 종료 시간 기준으로 오름차순 정렬 (종료시간 같을 시, 시작 시간 기준)
// 2. 회의가 끝나는 시간을 기준으로 가장 빨리 끝나는 회의 선택
