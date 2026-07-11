#include <iostream>
#include <queue>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n = 0;
    cin >> n;

    if ( n == 1 ) {
        cout << 1 << "\n";
        return 0;
    }

    queue<int> q;
    
    for (int i = 1; i <= n; i++) {
        q.push(i);
    }

    int temp = 0;
    for (int i = 0; i < n; i++) {
        q.pop();

        if (q.size() == 1) {
            break;
        }

        temp = q.front();       //값이 사라지지 않기때문에 수동으로 한 번더 삭제 해줘야함
        q.pop();
        q.push(temp);
    }

    cout << q.front() << "\n";

    return 0;
}

