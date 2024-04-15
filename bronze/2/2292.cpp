#include <iostream>

using namespace std;

int main() {
    int n = 0;
    cin >> n;

    int sum = 1, cnt = 1;
    
    while ( n > sum ) {   //근사값 까지
        sum += (cnt * 6);
        cnt++;
    }

    cout << cnt;

    return 0;
}
