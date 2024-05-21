#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N;
    cin >> N;

    vector<int> arr(N);
    vector<int> dp, lis_idx(N);

    for (int i = 0; i < N; i++)
    cin >> arr[i];

    for (int i = 0; i < N; i++) {
        int start = 0, end = dp.size();

        while (start < end) {
            int mid = (start + end) / 2;

            if (dp[mid] < arr[i])
                start = mid + 1;

            else
                end = mid;
        }

        if (start < dp.size())
            dp[start] = arr[i];

        else
            dp.push_back(arr[i]);

        lis_idx[i] = start;
    }

    int len = dp.size();

    vector<int> lis_seq(len);

    int idx = len - 1;

    for (int i = N - 1; i >= 0; i--) {
        if (lis_idx[i] == idx) {
            lis_seq[idx] = arr[i];
            idx--;
        }
    }

    cout << len << "\n";

    for (int i = 0; i < len; i++)
        cout << lis_seq[i] << " ";

    return 0;
}
