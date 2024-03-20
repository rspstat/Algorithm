#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);  cout.tie(NULL);

    int n = 0;  //총 케이스 개수
    cin >> n;
    int a[n] = {0};

    if ( n == 0 ) { // 아무 의견도 없으면 0 출력 후 종료
        cout << 0 << endl;
        return 0;
    }

    for (int i = 0; i < n; i++) //배열 입력
    cin >> a[i];

    sort(a, a+n);   //오름차순 정렬

    int result = round(n * 0.15);   //절사 값을 int 형태로 받음
    double sum = 0;     //합계 double로 선언

    for (int j = result; j < n - result; j++)   //절사값 제외 합계 구함
        sum+=a[j];

    int res = 0;
    res = int(round(sum / (n - result * 2 )));  //정수 형태로 최종 결과값 받음

    cout << res;

    return 0;
}
