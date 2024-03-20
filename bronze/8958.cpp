#include <iostream>
#include <string>

using namespace std;

int main() {
    int num, score, temp, len = 0;
    string str;

    cin >> num;
    cin.ignore();   //5 다음에 null 문자도 입력되기에 ignore

    for (int i = 0; i < num; i++) {
        getline(cin, str);
        int temp = 0;       //temp를 초기화 해줘야 첫 번쨰 출력값이 제대로 나옴

        for (int j = 0; j < str.length(); j++) {
            if (str[j] == 'O') {    //temp는 1부터 시작해서 1씩 더하면서 쭊 더해줌
                temp++;
                score+=temp;
            }

            else if (str[j] == 'X')
                temp = 0;       //x를 만나면 temp는 0이 되서 다음부터 초기화됨
        }

        cout << score << endl;
        score = 0;              //각각 초기화 해줌
        temp = 0;
    }

    return 0;
}

