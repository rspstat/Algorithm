#include <iostream>

using namespace std;

int main() {
    int a = 0;
    int num[30] = { 0 }; //학생 번호 입력받을 배열

    for (int i = 0; i < 28; i++) {  //조건이 28줄임
        cin >> a;
        num[a-1] = a;     //행만큼 그 순번대로 넣음
    }

    for (int j = 0; j < 30; j++) {
        if (num[j] == 0)      //배열 값에 0을 찾으면
            cout << j+1 << endl;     //그 출력값 출력
    }

    return 0;
}
