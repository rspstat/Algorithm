//1149번 RGB 거리
#include <iostream>

using namespace std;

int dp[1001][3] = {0,};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N = 0, res = 0;
    
    cin >> N;

    for (int i = 1; i <= N; i++) { 
        //첫 집을 R or G or B로 하는지에 대한 각각의 경우의 수임, RGB로 접근하면 안됨 XXX
        cin >> dp[i][0] >> dp[i][1] >> dp[i][2];  //R로 시작하냐 G로 시작하냐 B로 시작하냐

        //양쪽집 같은색 하면 안되니까, 각 전 집의 색을 빼고 최솟값을 더함
        dp[i][0] += min(dp[i-1][1], dp[i-1][2]);    //R로 시작한 경우
        dp[i][1] += min(dp[i-1][0], dp[i-1][2]);    //G로 시작한 경우
        dp[i][2] += min(dp[i-1][0], dp[i-1][1]);    //B로 시작한 경우
    }

    //마지막 집까지 시행하고 난 후, 최소 비용 구하기
    res = min(dp[N][0], min(dp[N][1], dp[N][2]));    //min 쓸 때, 3개 이상 비교하고 싶으면, 괄호 꼭 min으로 2개씩 묶어서 하기

    cout << res;

    return 0;
}

