#define ll long long
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

ll binarysearch(vector<int>& v, int N) {
    ll start = 1; // 랜선의 최소 길이
    ll end = *max_element(v.begin(), v.end()); // 최대 길이, algorithm 헤더
    ll result = 0; // 최대 랜선 길이

    while (start <= end) {
        ll mid = (start + end) / 2; 
        ll count = 0; // 중간값으로 잘랐을 때 얻을 수 있는 랜선의 총 개수
        
        for (int lanCable : v)  // 주어진 랜선들을 mid 길이로 잘라서 얻을 수 있는 랜선의 개수 계산
            count += lanCable / mid;

        if (count >= N) {  // 원하는 (N)보다 많거나 같게 만들 수 있다면, 길이를 늘려본다
            result = mid; // 최대 길이 갱신
            start = mid + 1;
        }

        else 
            end = mid - 1;    
    }

    return result; // 최대 길이 반환
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int K, N;
    cin >> K >> N;

    vector<int> v(K);

    for (int i = 0; i < K; i++)
        cin >> v[i];

    ll maxLen = binarysearch(v, N);

    cout << maxLen << "\n";

    return 0;
}
