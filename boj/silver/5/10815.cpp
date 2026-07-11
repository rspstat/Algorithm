    #include <iostream>
    #include <vector>
    #include <algorithm>

    using namespace std;

    vector<int> a;

    int search(int start, int end, long long int num ) { // 이분탐색 알고리즘
        while ( start <= end ) {
            int mid = (start + end) / 2;

            if ( a[mid] == num ) {
                return 1;
            }

            else if ( a[mid] > num ) {
                end = mid - 1;
            }

            else {
                start = mid + 1;
            }
        }

        return 0;
    }

    int main() {
        ios::sync_with_stdio(0);
        cin.tie(0); cout.tie(0);

        int n, n2 = 0;  //첫 번째 벡터 배열 크기, 두 번째 벡터 배열 크기

        cin >> n;

        int cnt = 0;
        for (int i = 0; i < n; i++) {   //윗 배열 입력 받아서 뒤로 삽입
            cin >> cnt;
            a.push_back(cnt);
            cnt = 0;
        }

        sort(a.begin(), a.end());

        cin >> n2;

        long long int ele = 0;
        for (int i = 0; i < n2; i++) {
            cin >> ele;
            cout << search(0, n - 1, ele) << " ";
        }

        return 0;
    }
