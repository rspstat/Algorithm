#include <bits/stdc++.h>

using namespace std;

int a, b;
bool visited[10000];

void bfs() {
    queue<pair<int, string>> q;
    q.push(make_pair(a, ""));
    visited[a] = true;

    while (!q.empty()) {
        int cur1 = q.front().first;
        string cur2 = q.front().second;
        q.pop();

        if ( cur1 == b ) {
            cout << cur2 << '\n';
            return;
        }

        int D, S, L, R;
    
        D = (cur1 * 2) % 10000;
        if (!visited[D]) {
            visited[D] = true;
            q.push(make_pair(D, cur2 + "D"));
        }

        S = cur1 - 1 < 0 ? 9999 : cur1 - 1;
        if (!visited[S]) {
            visited[S] = true;
            q.push(make_pair(S, cur2 + "S"));
        }

        // 1234 -> 2341 -> 3412 -> ...
        L = (cur1 % 1000) * 10 + (cur1 / 1000);
        if (!visited[L]) {
            visited[L] = true;
            q.push(make_pair(L, cur2 + "L"));
        }

        // 1234 -> 4123 -> 3412 -> ...
        R = (cur1 / 10) + (cur1 % 10) * 1000;
        if (!visited[R]) {
            visited[R] = true;
            q.push(make_pair(R, cur2 + "R"));
        }
    }
} 

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        cin >> a >> b;
        memset(visited, false, sizeof(visited)); // 초기화
        bfs();
    }

    return 0;
}

// D: D 는 n을 두 배로 바꾼다. 결과 값이 9999 보다 큰 경우에는 10000 으로 나눈 나머지를 취한다. 그 결과 값(2n mod 10000)을 레지스터에 저장한다.
// S: S 는 n에서 1 을 뺀 결과 n-1을 레지스터에 저장한다. n이 0 이라면 9999 가 대신 레지스터에 저장된다.
// L: L 은 n의 각 자릿수를 왼편으로 회전시켜 그 결과를 레지스터에 저장한다. 이 연산이 끝나면 레지스터에 저장된 네 자릿수는 왼편부터 d2, d3, d4, d1이 된다.
// R: R 은 n의 각 자릿수를 오른편으로 회전시켜 그 결과를 레지스터에 저장한다. 이 연산이 끝나면 레지스터에 저장된 네 자릿수는 왼편부터 d4, d1, d2, d3이 된다.
