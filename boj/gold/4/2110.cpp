#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool cpr(const vector<int>& router, int dis, int C) {   //주어진 거리로 배치할 수 있냐 없냐
    int cnt = 1, pos = router[0]; 

    for (int i = 1; i < router.size(); i++) {
        if (router[i] - pos >= dis) { //현재 집과 마지막으로 설치한 공유기 사이의 거리가 주어진 거리 이상이면
            cnt++; // 공유기 설치
            pos = router[i]; //마지막 위치 갱신
        }
    }

    if (cnt >= C) //C개의 공유기를 전부 설치할 수 있는가
        return true;
    else
        return false;
}

int binary_search(const vector<int>& router, int C) {   //이분탐색으로 최대 거리 찾기
    int start = 1, end = router.back() - router[0], res = 0;

    while (start <= end) {
        int mid = (start + end) / 2;

        if (cpr(router, mid, C)) {
            res = mid; 
            start = mid + 1; //더 큰 거리로 트라이
        } 
        
        else 
            end = mid - 1; //더 작은 거리로 트라이
    }

    return res; //답 반환
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, C;
    cin >> N >> C;

    vector<int> router(N);

    for (int i = 0; i < N; i++) 
        cin >> router[i];

    sort(router.begin(), router.end()); //오름차순

    int res = binary_search(router, C); 

    cout << res;

    return 0;
}
