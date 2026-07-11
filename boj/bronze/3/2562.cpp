#include <iostream>

using namespace std;

int main() {

    int a, max = 0;
    int arr[9];


    for (int i = 0; i < 9; i++) {
        cin >> arr[i];
    }

    max = arr[0];

    for (int j = 0; j < 9; j++) {
        if ( max < arr[j] ) {
            max = arr[j];
        }

        if ( max == arr[j]) {
            a = j;
        }
    }

    cout << max << endl << a + 1 << endl;
 
    return 0;
}
