#include <iostream>

using namespace std;

int main() {

    int cnt = 0;

    cin >> cnt;

    for (int i = 1; i <= cnt; i++) {       //줄 개수, 다이아몬드 위
        for (int j = cnt-1; j >= i; j--) {          //공백 개수
            cout << " ";
        }

        for (int h = 1; h <= (i*2) - 1; h++) {     //별 개수
            cout << "*";

        }
        cout << endl;

    }

    for (int l = 1; l < cnt; l++) {       //줄 개수, 아래, 첫번째줄 ~ cnt-1 줄 까지
        for (int m = 1; m <= l; m++) {     //공백 개수 ex) 첫번쨰줄에선 1개, 2번째 줄에선 2개....
            cout << " ";
        }

        for (int n = (cnt*2) - 1; n >= (2*l) +1; n--) {    //별 개수, 7개 부터 ~ ( l은 점점 오름 ), 즉 별 개수가 점점 줄음
            cout << "*";
        }

        cout << endl;
    }
    return 0;
}

//줄 개수
//별 개수
//띄어쓰기 개수
