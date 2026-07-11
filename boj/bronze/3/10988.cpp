#include <iostream>
#include <string>

using namespace std;

int main() {

    string str;

    getline(cin, str);

    int len,res = 0;
    len = str.length();

    for (int i = 0; i < len; i++) {
        if ( str[i] == str[len-i-1] ) {
            res = 1;
        }

        else {
            res = 0;
            break;
        }
    }

    cout << res << endl;


    return 0;
}
