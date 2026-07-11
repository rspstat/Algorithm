#include <iostream>

using namespace std;

int main() {

    long long int s = 0; //문제 조건이 42억까지

    cin >> s;   //서로 다른 수 N들의 합을 입력 받음

    long long int sum = 0;    //1부터 더해서 저장할 변수 -> 1+2+3+4+~~~
    int b = 0;      //더한 횟수 (몇개의 자연수)
    int c = 0;      //증가할 변수

    while (1) {     //계속 실행
        c++;        //1씩 c를 증가시킴
        sum += c;   //합 변수에 c를 더해서 다시 대입 -> 1) sum = 1 + 0 / 2) sum = 1 + 1 ... 이런식으로 1+2+3+~~ 가 만들어지게됨

        if ( sum > s ) //계속 더하다가 주어진 합을 넘으면
            break;  //탈출

        else        //아니면 계속 더하고
            b++;    //더한 횟수 증감
    }
    

    cout << b;      //출력

    return 0;

}
