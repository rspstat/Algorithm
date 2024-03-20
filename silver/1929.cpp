#include <iostream>
#include <cmath>

using namespace std;

int arr[1000001];

int main() {
    int a, b = 0;
    cin >> a >> b;

    // int num[b-a];
    // int no_num[b-a];

    for (int c = 2; c <= b; c++)
        arr[c] = c;


    for (int i = 2; i <= sqrt(b); i++) {
        if ( arr[i] == 0) {
            continue;
        }
        for (int j = i*i; j <= b; j+=i) {
            arr[j] = 0;
        }
    }

    for (int q = a; q <= b; q++) {
        if ( arr[q] == 0 ) {
            continue;
        }

        cout << arr[q] << '\n';
    } 
    

    return 0;
}
