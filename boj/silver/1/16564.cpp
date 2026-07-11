#include <iostream>
#include <algorithm>
#include <vector>

#define ll long long

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N = 0; 
    ll K = 0;

    cin >> N >> K;

    vector<int> x;

    for (int i = 0; i < N; i++) {
        ll lv = 0; //push_back 할 때, 이거 초기화 꼭 해줘...
        cin >> lv;
        x.push_back(lv);
    }

    sort(x.begin(), x.end());

    //binary_search, 이분탐색
    ll start = x[0], end = x[0] + K, mid = 0, res = 0, cnt = 0;

    while (start <= end) {
            mid = (start + end) / 2;
            cnt = 0;

        for (int i = 0; i < N; i++) {
            if ( mid > x[i] ) 
                cnt += (mid - x[i]);    //핵심

            else
                break;
        }

        if ( cnt > K ) 
            end = mid - 1;

        else {
            res = mid;
            start = mid + 1;
        }
    }

    cout << res;

    return 0;
}
