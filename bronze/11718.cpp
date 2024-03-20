#include <iostream>
#include <string>
#include <string.h>

using namespace std;

int main() {

    string str;

    int len = 0;
    len = str.length();

    for (int i = 0; i < 100; i++) {
        getline(cin, str);
        cout << str << endl;
    }

    return 0;
}


