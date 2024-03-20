#include <iostream>
#include <algorithm>

using namespace std;

int main() {

    int n, m = 0;
    int i, j = 0;

    cin >> n >> m;

    int basket[n + 1] = { 0 };

    for (int h = 1; h <= n; h++)     //바구니 번호대로 배열 작성 ex) (1,2,3,4,5)
        basket[h] = h;

    for (int c = 1; c <= m; c++) {
            cin >> i >> j;
            reverse(basket + i, basket + j + 1);
    }

    for (int b = 1; b <= n; b++) 
        cout << basket[b] << " ";

    return 0;
}
