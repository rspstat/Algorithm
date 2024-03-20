#include <iostream>
#include <string>
#include <string.h>

using namespace std;

int main() {

    // string str;

    char str[21];

    int t, r = 0; //테스트 개수, 반복할 횟수

    cin >> t;

    for (int i = 0; i < t; i++) {
        cin >> r;  // 반복할 횟수
        cin >> str; // 문자열

        int len = 0;
        len = strlen(str);

        for (int k = 0; k < len; k++) {
            for (int j = 0; j < r; j++) {
                cout << str[k];
            }
        }
        cout << endl;
    }


    return 0;

}


