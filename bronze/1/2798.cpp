#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m, res, max = 0;   //카드 개수, 구하려는 수
    cin >> n >> m;

    int arr[n] = {0};

    for (int i = 0; i < n; i++)
        cin >> arr[i];
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                res = arr[i] + arr[j] + arr[k];
                if (res > m) {      //이 if문의 두 조건을 만족해야 최대한 값을 찾을 수 있음. (else는 안됨.)
                    continue;
                }

                if (max < res) {
                    max = res;
                }
            }
        }
    }

    cout << max;

    return 0;
}
