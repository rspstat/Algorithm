#include <bits/stdc++.h>

using namespace std;

int main() { 
    int N, r, c;
    cin >> N >> r >> c;

    int res = 0;
    int size = pow(2, N);   // 배열의 크기 2^N

    while (size > 1) {
        int h = size / 2;

        if (r < h && c < h) {
            // 변화 X
        }

        // base case로 생각해보면, 00, 01, 10, 11 이건데, half보다 행은 작고, 열은 크니까... 2사분면으로 가버리는거지...
        // 그니까 만약 basecase (2x2) 행렬이라 치면 여기서 4개로 쪼개서 사분면으로 보고... 거기서 값을 계산하는거임...
        else if (r < h && c >= h) { 
            res += h * h;
            c -= h;
        }

        else if (r >= h && c < h) {
            res += 2 * h * h;
            r -= h;
        }

        //11이라 치면, 답은 3인데,,, h가 1이므로,, 여기로 들어가서  res값이 3이 됨... 오케이
        else {  
            res += 3 * h * h;
            r -= h;
            c -= h;
        }

        size = h;
    }

    cout << res << endl;

    return 0;
}
