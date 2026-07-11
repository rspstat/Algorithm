#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, tmp, tmp2 = 0;
    cin >> n;

    vector<pair<int, int>> arr;

    for (int i = 0; i < n; i++) {
        cin >> tmp >> tmp2;
        arr.push_back(make_pair(tmp, tmp2));
        tmp, tmp2 = 0;
    }

    sort(arr.begin(), arr.end());
    
    for (int j = 0; j < n; j++) {
        cout << arr[j].first << " " << arr[j].second << "\n";
    }

    return 0;
}


// vector 2차원 배열 페어 이용
