#include <iostream>
#include <unordered_set>
using namespace std;

int grundy[1010];

int mex(unordered_set<int> s) {
    int a = 0;
    while(s.count(a)) {
        a++;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    grundy[0] = 0;
    grundy[1] = 0;
    grundy[2] = 1;

    for(int i = 3; i <= n; i++) {
        unordered_set<int> s;
        
        for(int j = 1; j <= i / 2; j++) {
            // 이웃한 두 변을 잇는 경우 (삼각형 하나 제거)
            if(j == 1) {
                s.insert(grundy[i - 2]);
            }
            // 대각선으로 양쪽을 분할하는 경우
            else {
                s.insert(grundy[j - 1] ^ grundy[i - j - 1]);
            }
        }

        grundy[i] = mex(s);
    }

    cout << (grundy[n] ? 1 : 2) << "\n";

    return 0;
}
