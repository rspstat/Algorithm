#include <iostream>

using namespace std;

int main() {

    int n, m = 0;

    cin >> n >> m;

    int basket[100] = { 0 };

    for (int b = 0; b < n; b++)               //바구니에 있는 공의 번호 (바구니랑 같음)
        basket[b] = b + 1;                              //0부터가 첫번째 바구니임
    
    int i, j = 0;
    int temp = 0;

    for (int a = 0; a < m; a++) {                       //케이스의 개수만큼 입력받음
        cin >> i >> j;

        temp = basket[i - 1];
        basket[i - 1] = basket[j - 1];
        basket[j - 1] = temp;                   //교환 알고리즘인데 0부터 시작한 배열이라 -1 해야함
    }

    for (int c = 0; c < n; c++)
        cout << basket[c] << " ";
    

    return 0;
}
