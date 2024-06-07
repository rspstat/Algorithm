#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

void insert(map<int, long long int>& v, vector<long long int>& sum, int x);

int main() {
    ios::sync_with_stdio(0);    // 실제로는 printf, scanf가 빠르다.
    cin.tie(0); cout.tie(0);    // C++에서 C의 stdio buffer를 동기화하는 과정에서 딜레이 발생하기 때문.

    map<int, long long int> tree;
    tree.insert(pair<int, long long int> {0, -1});  // 초기값 삽입
    tree.insert(pair<int, long long int> (300001, -1));  // 최대값 삽입

    int n, m;

    cin >> n;  // 입력 개수 받기

    vector<long long int> sum;

    while (n--) {  // 입력 개수만큼 반복
        cin >> m;  // 입력 값 받기
        insert(tree, sum, m);  // 트리에 삽입
    }

    for (long long int x : sum) 
        cout << x << "\n";  // %lld 출력

    return 0;
}

void insert(map<int, long long int>& v, vector<long long int>& sum, int x) {
    map<int, long long int>:: iterator lower_bound;
    map<int, long long int>:: iterator upper_bound;

    lower_bound = --v.lower_bound(x);  // x보다 작은 값 중 가장 큰 값 찾기
    upper_bound = v.upper_bound(x);  // x보다 큰 값 중 가장 작은 값 찾기

    long long int cnt = 0;

    cnt = max(lower_bound->second, upper_bound->second) + 1;  // 두 값 중 큰 값에 1 더하기

    v.insert(pair<int, long long int> {x, cnt});  // 새로운 값 삽입

    if (sum.size() > 1) 
        sum.push_back(sum[sum.size() - 1] + cnt);  // 누적합 업데이트
    
    else 
        sum.push_back(cnt);  // 첫 번째 값 처리
    
    return ;    // void 함수에서 함수 종료 선언
}
