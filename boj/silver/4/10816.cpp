#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int bound(vector<int>& arr1, int target);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m = 0;
    cin >> n;

    vector<int> arr1(n);

    for (int i = 0; i < n; i++) 
        cin >> arr1[i];

    sort(arr1.begin(), arr1.end());

    cin >> m;

    int temp = 0;

    int result[m] = {0,};

    for (int i = 0; i < m; i++) {
        cin >> temp;
        
        if ( bound(arr1,temp) != -1 )     //값을 찾을 때만
            result[i] = bound(arr1, temp);  //결과 배열에 대입
    }

    for (int i = 0; i < m; i++)
        cout << result[i] << " ";

    return 0;
}  

int bound(vector<int>& arr1, int target) {      // algorithm 헤더에 포함된 중복포함 이진 탐색 함수 실행
    auto lower = lower_bound(arr1.begin(), arr1.end(), target);   //자료형을 알아서 설정하는 auto 변수 (c++11 부터 생김)
    auto upper = upper_bound(arr1.begin(), arr1.end(), target);   //auto를 안쓰려면 vector<int>::iterator lower, upper 이런식으로 써야함

    if (lower == arr1.end() || *lower != target) 
        return -1;  // 값이 배열에 없음

    else 
        return upper - lower;  // 중복된 값의 수 반환, ex) 0 0 0 -> 0 = lower, 2 = upper --> 2 - 0 = 2 리턴
}
