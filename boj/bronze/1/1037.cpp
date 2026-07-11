#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n = 0;
    cin >> n;

    vector<int> a;

    int element = 0;
    for (int i = 0; i < n; i++) {   //a 벡터 배열의 원소를 입력 받아서 뒤에서 삽입
        cin >> element;
        a.push_back(element);
        element = 0;
    }

    sort(a.begin(), a.end());

    int res = 0;   
    res = a.front() * a.back();

    cout << res << endl; 

    return 0;
}
