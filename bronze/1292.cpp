#include <iostream>

using namespace std;

int main() {
    int a, b, sum = 0;
    int k = 1;

    int arr[1001] = {0, };

    for (int i = 1; i <= 1000; i++) {    //총 1000번 실행
        for (int j = 1; j <= i; j++) {   //ex) i==2 면 2번 넣음
            arr[k] = i;

            if ( k > 1000 )
                break;

            k++;
        }
    }
    cin >> a >> b;

    for (int c = a; c <= b; c++) 
        sum += arr[c];

    cout << sum << endl;
        
    
    return 0;
}

// 범위 잘 해야함
