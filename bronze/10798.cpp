#include <iostream>
#include <string>

using namespace std;

int main() {

	char str[5][15] = {0};

    for ( int i = 0; i < 5; i++)
        cin >> str[i];      //각 행마다 입력 받음 //나머지는 0임


    for (int j = 0; j < 15; j++) {      
        for (int h = 0; h < 5; h++) {
            if (str[h][j] != '\0')
                cout << str[h][j];      //쭉 검사하다가 0이 아닌 문자들을 출력함
        }
    }
    
    cout << endl;

    return 0; 
}
