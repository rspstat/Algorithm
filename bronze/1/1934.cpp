#include <iostream>

using namespace std;

int gcd(int num1, int num2, int temp = 0);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, num1, num2 = 0;
    cin >> n;

    int result[n];

    for (int i = 0; i < n; i++) {
        cin >> num1 >> num2;
        result[i] = num1 * num2 / gcd(num1, num2);    //최소 공배수 구하기 (첫 숫자 * 두번째 숫자 / 최대 공약수)
    }

    for (int i = 0; i < n; i++) 
        cout << result[i] << "\n";

    return 0;
}

int gcd(int num1, int num2, int temp) {   //유클리드 호제법 최대 공약수

    while (num2 != 0) {
        temp = num1 % num2;
        num1 = num2;
        num2 = temp;
    }

    return num1;
}
