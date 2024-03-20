#include <iostream>
#include <algorithm>

using namespace std;

char WB[8][8] = {       //브루드포스 알고리즘
	'W','B','W','B','W','B','W','B',
	'B','W','B','W','B','W','B','W',
	'W','B','W','B','W','B','W','B',
	'B','W','B','W','B','W','B','W',
	'W','B','W','B','W','B','W','B',
	'B','W','B','W','B','W','B','W',
	'W','B','W','B','W','B','W','B',
	'B','W','B','W','B','W','B','W'
};

char BW[8][8] = {
	'B','W','B','W','B','W','B','W',
	'W','B','W','B','W','B','W','B',
	'B','W','B','W','B','W','B','W',
	'W','B','W','B','W','B','W','B',
	'B','W','B','W','B','W','B','W',
	'W','B','W','B','W','B','W','B',
	'B','W','B','W','B','W','B','W',
	'W','B','W','B','W','B','W','B'
};

int main() {

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m = 0;
    cin >> n >> m;

    char str[n][m];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> str[i][j];
        }
    }

    int cnt_b, cnt_w, ans = 0;
    int res = 64;       //나올 수 있는 경우의 수 최댓값

    for (int h = 0; h <= n-8; h++) {        //범위에서 시작 위치 정하기
        for (int l = 0; l <= m-8; l++) {    // "
            	int cnt_w = 0, cnt_b = 0; //블랙, 화이트 개수 초기화
			for (int x = 0; x < 8; x++) { //BW, WB 체스판 비교 반복문
				for (int y = 0; y < 8; y++) {
					if (str[h + x][l + y] != BW[x][y]) { //BW랑 비교
						cnt_b++;
					}
					if (str[h + x][l + y] != WB[x][y]) { //WB랑 비교
						cnt_w++;
					}
				}
			}
			//최솟값 비교, algorithm 헤더 파일 사용
			ans = min(cnt_b, cnt_w);
			if (ans <= res) {
				res = ans;
			}
		}
	}

	cout << res;

    return 0;

}
