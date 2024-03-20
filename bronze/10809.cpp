#include <iostream>
#include <string>

using namespace std;

int main() {

    string str;

    cin >> str;

    for (int j = 97; j <= 122; j++) {

        if ( str.find(j) == string::npos )  //아스키코드 97(a) ~ 122(z)까지 찾는데 못찾을 경우,
            cout << "-1 ";

        else
            cout << str.find(j) << " ";     //찾는 경우, str.find(j) 찾는 인덱스 값을 반환함
    }

    return 0;
}
