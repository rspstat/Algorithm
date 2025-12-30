#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int arr[10], tmp[10];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void tog(int r, int c) {
    tmp[r] ^= (1 << c);
    for (int i = 0; i < 4; i++) {
        int nr = r + dx[i];
        int nc = c + dy[i];
        if (nr >= 0 && nr < 10 && nc >= 0 && nc < 10)
            tmp[nr] ^= (1 << nc);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    for (int i = 0; i < 10; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < 10; j++) {
            if (s[j] == 'O') arr[i] |= (1 << j);
        }
    }

    int ans = 101;

    // 첫 번째 줄의 1024가지 경우의 수를 모두 시도
    for (int step = 0; step < (1 << 10); step++) {
        int cnt = 0;
        for (int i = 0; i < 10; i++) tmp[i] = arr[i];

        for (int j = 0; j < 10; j++) {
            if (step & (1 << j)) {
                tog(0, j);
                cnt++;
            }
        }

        // 두 번째 줄부터는 바로 윗줄의 켜진 불을 끄기 위해 스위치 조작이 고정됨
        for (int i = 1; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (tmp[i - 1] & (1 << j)) {
                    tog(i, j);
                    cnt++;
                }
            }
        }

        if (tmp[9] == 0) ans = min(ans, cnt);
    }

    if (ans == 101) cout << -1;
    else cout << ans;

    return 0;
}
