#include <iostream>

using namespace std;

int main() {

    int N, M = 0;           //N == 바구니 갯수, M == 공을 넣는 방법 케이스 개수
    int i, j, k = 0;        //i~j 번 바구니까지 k번의 공을 넣음

    cin >> N >> M;  

    int basket[101] = { 0 };

    for (int z = 0; z < M; z++) {    //케이스의 개수 만큼 ijk를 입력 받음

        cin >> i >> j >> k;

        for (int x = i; x <= j; x++) {    //i번째 바구니부터 j번째 바구니 까지 반복
            basket[x] = k;              //바구니 마다 공을 넣음
        }      
    }

    for (int c = 1; c <= N; c++) {

        cout << basket[c] << " ";
    }

    return 0;
}
