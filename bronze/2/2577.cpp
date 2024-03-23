#include <iostream>
#include <string>

using namespace std;

int main() {
    int a, b, c = 0;

    cin >> a >> b >> c;

    int num = 0;
    num = a*b*c;

    int arr[10] = {0,0,0,0,0,0,0,0,0,0};
    int temp = 0;

    for (int i = num; i > 0; i/=10) {
        temp = i%10; 
        arr[temp]++;
    }



    for (int h = 0; h < 10; h++){
        cout << arr[h] << endl;
    }

    return 0;
}
