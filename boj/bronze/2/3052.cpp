#include <iostream>

using namespace std;

int main() {
    int arr[10] = { 0 };
    int arr2[42] = { 0 };
    int z = 0;

    for (int i = 0; i < 10; i++) 
        cin >> arr[i];

    for (int j = 0; j < 10; j++) {
        z = arr[j];
        arr2[z % 42] = 1;         
    }
    
    int m = 0;

    for (int h = 0; h < 42; h++) {
        if (arr2[h] == 1){
            m++;
        }
    }

    cout << m << endl;
    
    return 0;
}
