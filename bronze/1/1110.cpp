#include <iostream>

using namespace std;

int main() {

    int n, temp, newnum, c = 0;

    cin >> n;
    temp = n;

    do {
        // 먼저 주어진 수가 10보다 작으면 앞에 0을 붙여 두 자리 수로 만듭니다.
        int left = n / 10; // 주어진 수의 왼쪽 자리
        int right = n % 10; // 주어진 수의 오른쪽 자리

        // 각 자리의 숫자를 더합니다.
        int sum = left + right;

        // 새로운 수를 만듭니다: 주어진 수의 오른쪽 자리 수와 앞에서 구한 합의 가장 오른쪽 자리 수를 이어 붙입니다.
        newnum = right * 10 + sum % 10;

        n = newnum;

        c++;

    } while (n != temp); // 새로운 수가 처음 주어진 수와 같아질 때까지 반복합니다.

    // 사이클 길이를 출력합니다.
    cout << c << endl;

    return 0;
}

// #include <iostream>
// using namespace std;

// int main() {
//     int n, temp, cycle = 0;
//     cin >> n;
//     temp = n;

//     do {
//         // 현재 수의 각 자리 수를 더하고, 그 합의 오른쪽 자리 수와 현재 수의 오른쪽 자리 수를 결합

//         temp = (temp % 10) * 10 + (temp / 10 + temp % 10) % 10;

//         cycle++; // 사이클 카운트 증가

//     } while (temp != n); // 입력받은 수로 돌아올 때까지 반복

//     cout << cycle; // 사이클 길이 출력

//     return 0;
// }
