#include <iostream>
#include <stdio.h>

using namespace std;

int main() {

    int a, b = 0;
    // int num1[3], num2[3];
    int num[6];

    scanf("%d %d", &a, &b);

    int temp, temp2, n, n1 = 0;

    num[2] = a / 100;
    num[1] = (a % 100) / 10;
    num[0] = a % 10;

    num[5] = b / 100;
    num[4] = (b%100) / 10;
    num[3] = b % 10;

    n = (num[0] * 100) + (num[1]*10) + num[2];
    n1 = (num[3] * 100) + (num[4]*10) + num[5];

    if ( n < n1 ) 
        cout << n1 << endl;

    else
        cout << n << endl;

    return 0;
}


