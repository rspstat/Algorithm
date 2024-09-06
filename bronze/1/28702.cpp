#include <iostream>
#include <string> 

using namespace std;

int main() {
    string str[3];
    int tmp = 0;
    int idx = 0;

    for (int i = 0; i < 3; i++) {
        cin >> str[i];

        if ( str[i][0] >= '0' && str[i][0] <= '9' ) {   // 첫 글자가 0~9까지인 문자열이 있다면,
            tmp = atoi(str[i].c_str()); // str[i] -> str에서 char*로 변환하고 integer로 변환
            idx = i;    // index 추출
        }
    } 

    int res = tmp + 3 - idx;   // ex) 11이 3번째 -> 11 + 3 - 2(idx) = 12번째 추출 가능 if문보다 간결함

    if ( res % 15 == 0 ) cout << "FizzBuzz";
    else if ( res % 3 == 0 ) cout << "Fizz";    // 5의 배수가 아니라는 조건은 3의 배수면 이미 출력되므로 생략 가능.
    else if ( res % 5 == 0 ) cout << "Buzz";    // 3의 배수가 아니라는 조건은 이미 먹고 들어감
    else cout << res;

    return 0;
}
