#include <iostream>

using namespace std;

int main() {
    int a, max, min = 0;

    cin >> a;

    int arr[a];

    for (int i = 0; i < a; i++)     //배열의 값을 차례대로 입력받아 배열에 삽입
    cin >> arr[i];

    max = arr[0];                   //배열의 첫 값을 최댓값, 최솟값 변수에 각각 삽입
    min = arr[0];

    for (int j = 0; j < a; j++) {       
        if ( max < arr[j])          //0열 부터 max 변수보다 크면 그 변수를 max 변수에 삽입 (초기값 : 0열 변수 값)
        max = arr[j] ;

        if ( min > arr[j])          //0열 부터 min 변수보다 작으면 그 변수를 min 변수에 삽입 (초기값 : 0열 변수 값)
        min = arr[j];
    }

    cout << min << " " << max << endl;

    return 0;
}
