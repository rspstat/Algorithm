#include <iostream>

using namespace std;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, cnt = 0;
    cin >> n;

    for (int i = 666; ; i++) {
        int tmp = i;
        while (tmp >= 666) {
            if (tmp % 1000 == 666) {
                cnt++;
                break;
            }

            tmp /= 10;
        }

        if (n == cnt) {
            cout << i;
            break;
        }
    }
}
