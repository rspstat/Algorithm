#include <iostream>
#include <queue>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;

    priority_queue<int, vector<int>, greater<int>> pq;  // 우선순위 큐 (최소 힙) 선언

    while (n--) {
        int a;
        cin >> a;

        if ( a != 0 ) 
            pq.push(a);
        
        else {
            if (pq.empty()) 
                cout << 0 << "\n";

            else {
                cout << pq.top() << "\n";
                pq.pop();
            }
        }
    }

    return 0;
}
