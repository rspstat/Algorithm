#include <iostream>

using namespace std;

int sumOfDigits(int num) {
    int sum = 0;

    while (num != 0) {  //n == 216인데 198이 왔어
        sum += num % 10;    //8 + 9 + 1 순으로 들어감
        num /= 10;          //나누기 때문에
    }

    return sum;
}

int main() {
    int n = 0, result = 0;
    cin >> n;

    for (int i = n; i >= 1; i--) {
        if ( n == i + sumOfDigits(i) ) { //216 == 198 + 1 + 9 + 8
            result = i;
        }
    }

    if ( result == 0 )
        cout << 0 << endl;

    else 
        cout << result << endl;

    return 0;
}
