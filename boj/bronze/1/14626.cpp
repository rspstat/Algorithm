#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string str;
    cin >> str;

    int sum = 0;
    int check = 0;

    for (int i = 0; i < 13; i++) {
        if (str[i] != '*') {    // 만약 훼손되지 않았으면
            if (i % 2 == 0) {   // 짝수 인덱스는 그대로 더하고
                sum += (str[i] - '0');
            }

            else {              // 홀수 인덱스는 3을 곱하여 더함
                sum += (str[i] - '0') * 3;
            }
        }

        else {      // 만약 훼손 됐으면
            if (i % 2 == 1) check = 1;      // check = 1; -> 홀수 인덱스 / check = 0; -> 짝수 인덱스
        }
    }

    int v = (check == 1) ? 3 : 1;       // 가중치 설정 -> 만약 홀수 인덱스가 훼손이면 v = 3, 아니면 v = 1

    for (int i = 0; i <= 9; i++) {      // 총 10번 시행하는데
        if ((i * v + sum) % 10 == 0) {      //  m = ~~ mod 10 값이 0이 되도록 하는 수 구하기
            cout << i << '\n';
            return 0;
        }
    }
}
