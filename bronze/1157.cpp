#include <iostream>
#include <string.h>

using namespace std;

int main() {

    string str;
    cin >> str;

    int len = 0;
    len = str.length();

    for (int i = 0; i < len; i++) { //대소문자 변환
        if ( str[i] >= 'a' && str[i] <= 'z') 
            str[i] -= 32;
    }

    int num[26] = {0,};
    int index = 0;

    for (char c : str) {
        if (c >= 'A' && c <= 'Z') {
            num[c - 'A']++;
        }
    }
    
    int max = num[0];
    for (int h = 0; h < 26; h++) {
        if ( max < num[h] ) {
            max = num[h];
            index = h;
        }
    }

    for (int k = index+1; k < 26; k++) {
        if ( num[index] == num[k] ) {
            cout << "?";
            return 0;
        }
    }

    char res;
    
    cout << char(res+index+65);

    return 0;
}
