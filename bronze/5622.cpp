#include <iostream>
#include <string>
#include <string.h>

using namespace std;

int main() {

    char str[16];

    cin >> str;

    int len = 0;
    len = strlen(str);

    int a[len];

    for (int i = 0; i < len; i++) {
        if ( str[i] == 'A' || str[i] == 'B' || str[i] == 'C') {
            a[i] = 3;
        }

                if ( str[i] == 'D' || str[i] == 'E' || str[i] == 'F') {
            a[i] = 4;
        }
                else if ( str[i] == 'G' || str[i] == 'H' || str[i] == 'I') {
            a[i] = 5;
        }
                else if ( str[i] == 'J' || str[i] == 'K' || str[i] =='L') {
            a[i] = 6;
        }
                if ( str[i] == 'M' || str[i] == 'N' || str[i] == 'O') {
            a[i] = 7;
        }   
                else if ( str[i] == 'P' || str[i] == 'Q' || str[i] == 'R' || str[i] == 'S') {
            a[i] = 8;
        }
                else if ( str[i] == 'T' || str[i] == 'U' || str[i] == 'V') {
            a[i] = 9;
        }

                else if ( str[i] == 'W' || str[i] == 'X' || str[i] == 'Y' || str[i] == 'Z') {
            a[i] = 10;
        }

    }

    int sum = 0;


    for (int j = 0; j < len; j++)
        sum += a[j];
    
        cout << sum;

    return 0;

}


