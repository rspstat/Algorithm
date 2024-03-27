#include <iostream>
#include <algorithm>

using namespace std;

int solve(int n, int size, int arr[]) { //이분탐색
    int start = 0;
    int end = size - 1;

    while ( start <= end ) {
        int mid = ( start + end ) / 2;

        if (arr[mid] == n) 
            return 1;

        else if (n < arr[mid]) 
            end = mid - 1;

        else 
            start = mid + 1;
    }

    return 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    int n, m, tmp, tmp2 = 0; 
    cin >> n;

    int arr[n] = {0};

    for (int i = 0; i < n; i++) { 
        cin >> arr[i];
    }

    sort(arr, arr+n);
    
    cin >> m;

    for (int i = 0; i < m; i++) {
        cin >> tmp2;
        cout << solve(tmp2, n, arr) << "\n";
    }

    return 0;
}
