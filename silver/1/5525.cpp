#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    string S;
    cin >> N >> M >> S;

    int ans = 0;
    int count = 0;
    int i = 1;

    while (i < M - 1) { // 문자열 길이 동안
        if (S[i - 1] == 'I' && S[i] == 'O' && S[i + 1] == 'I') {    // IOI 탐색
            count++;    // 카운트 ++
            if (count == N) {   // 만약 카운트 = 처음 입력한 문자의 개수?
                ans++;      // 답 ++
                count--;    // 카운트 --
            }

            i += 2; // IOI 다음 인덱스 접근
        } 
        
        else {      // 못찾으면
            count = 0;  // 카운트 초기화
            i++; // 한 칸 전진
        }
    }

    cout << ans;

    return 0;
}
