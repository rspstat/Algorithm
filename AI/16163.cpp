#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    // 입출력 속도 향상
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string S;
    cin >> S;

    // 1. Manacher 알고리즘을 위한 문자열 변형 (# 끼워넣기)
    string T = "#";
    for (char c : S) {
        T += c;
        T += "#";
    }

    int N = T.length();
    vector<int> A(N, 0); // 각 위치에서의 팰린드롬 반지름 크기 저장
    int c = 0; // 현재 가장 오른쪽까지 뻗은 팰린드롬의 중심
    int r = 0; // 그 팰린드롬의 오른쪽 경계

    long long count = 0; // 정답 (범위가 크므로 long long 필수)

    // 2. Manacher 알고리즘 수행
    for (int i = 0; i < N; i++) {
        // i가 r 내부에 있다면, 대칭점(mirror)의 정보를 활용하여 초기값 설정
        int mirror = 2 * c - i;
        
        if (i < r) {
            A[i] = min(r - i, A[mirror]);
        }

        // 중심 i에서 양옆으로 팰린드롬 확장
        // 범위를 벗어나지 않고, 좌우 문자가 같으면 확장
        while (i - A[i] - 1 >= 0 && i + A[i] + 1 < N && 
               T[i - A[i] - 1] == T[i + A[i] + 1]) {
            A[i]++;
        }

        // 팰린드롬이 오른쪽 경계를 넘어갔다면, 중심과 경계 갱신
        if (i + A[i] > r) {
            c = i;
            r = i + A[i];
        }

        // 3. 팰린드롬 개수 누적
        // 변형된 문자열에서의 반지름 A[i]를 이용하면
        // 원래 문자열에서 해당 중심의 팰린드롬 개수는 (A[i] + 1) / 2 가 됨
        count += (long long)(A[i] + 1) / 2;
    }

    cout << count << "\n";

    return 0;
}
