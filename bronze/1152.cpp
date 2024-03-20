#include <iostream>
#include <string>

using namespace std;

int main() {

    string str;

    getline(cin, str);

    int a, cnt = 0;

    int len = str.length();

    if ( str.front() != ' ' && str.back() != ' ') {     //1번 케이스

        for (int i = 0; i < len; i++) {  
            if ( str[i] == ' ' ) {
                cnt++;
            }
        }

        cnt += 1;
    }
    

    else if ( str.front() == ' ' && str.back() != ' ' ) {    //2번 케이스
        for (int i = 0; i < len; i++) {  
            if ( str[i] == ' ' ) {
                cnt++;
            }
        }
    }

    else if ( str.front() != ' ' && str.back() == ' ') {    //3번 케이스
        for (int i = 0; i < len; i++) {  
            if ( str[i] == ' ' ) {
                cnt++;
            }
        }
    }

    else if ( str.front() == ' ' && str.back() == ' ') {     //1번 케이스

        for (int i = 0; i < len; i++) {  
            if ( str[i] == ' ' ) {
                cnt++;
            }
        }

        cnt -= 1;
    }

    cout << cnt;;

    return 0;

}

//4가지 경우
//1. 공백이 앞 뒤로 없을 때, 2. 공백이 앞에 넣고 시작할떄, 3. 공백이 맨 뒤에 있을때 4. 공백이 앞 뒤로 있을때
