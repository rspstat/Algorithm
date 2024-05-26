#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n = 0, res = 0;
    cin >> n;

    bool arr[100][100] = {false};   //전부 false로 초기화 (0으로 초기화)

    while (n--) {
        int x, y;
        cin >> x >> y;
        for (int i = y; i < y + 10; i++) {
            for (int j = x; j < x + 10; j++) {
                if (arr[i][j]) //입력받은 부분은 참값이 됨 && 겹치는 부분은 건너뜀...
                    continue;

                arr[i][j] = 1;
                res++;
            }
        }
    }

    cout << res;

    return 0;
}

//문제 풀이 : 100 x 100 2차원 배열을 도화지로 생각하고
//입력을 받은  x,y 에 따라 1로 만든다
//ex) 00111111110000 이런 느낌...
