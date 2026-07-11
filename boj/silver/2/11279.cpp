#include <iostream>
#include <queue>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;

    priority_queue<int, vector<int>, less<int>> pq;

    while (n--) {
        int x;
        cin >> x;

        if ( x != 0 ) {
            pq.push(x);
        }

        else {
            if ( pq.empty() ) {
                cout << 0 << "\n";
            }

            else {
                cout << pq.top() << "\n";
                pq.pop();
            }
        }
    }

    return 0;
}
