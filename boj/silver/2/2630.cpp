#include <iostream>

using namespace std;

int map[129][129] = {0, };
int w = 0; int b = 0;

void divd_conq(int x, int y, int N) {
    int tmp_cnt = 0;
    for (int i = x; i < x + N; i++) {
        for (int j = y; j < y + N; j++) {
            if(map[i][j])
                tmp_cnt++;
        }
    }

    if (tmp_cnt == 0) w++;
    else if (tmp_cnt == N * N) b++;
    else {
        divd_conq(x, y, N / 2); // 1사분면
        divd_conq(x, y + N / 2, N / 2); // 2사분면
        divd_conq(x + N / 2, y, N / 2); // 3사분면
        divd_conq(x + N / 2, y + N / 2, N / 2); // 4사분면
    }
}

int main() {
    int n, tmp = 0;
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> tmp;
            map[i][j] = tmp;
        }
    }

    divd_conq(0, 0, n);
    cout << w << '\n' << b << '\n';

    return 0;
}
