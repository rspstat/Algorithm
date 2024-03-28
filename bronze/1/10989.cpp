#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int n, idx = 0;
    cin >> n;

    int arr[10001] = {0,};

    for (int i = 0; i < n; i++) {
        cin >> idx;      //1~10000 등장 횟수 기록
        arr[idx] += 1;   
    }

    for (int i = 1; i <= 10000; i++) {
        for (int j = 1; j <= arr[i]; j++) {     //배열을 순회하면서
            cout << i << "\n";      //등장한 횟수 만큼 해당 숫자 출력
        }
    }

    return 0;
}

//계수정렬
