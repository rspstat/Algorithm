#include <bits/stdc++.h>
using namespace std;

struct Comp {
    bool operator() (int a, int b) {
        if ( abs(a) == abs(b) ) 
            return a > b;       // 절댓값이 같은 경우 가장 작은 원소로
        return abs(a) > abs(b);    // 절대값이 작은 원소로로
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; 
    cin >> n;

    priority_queue<int, vector<int>, Comp> pq;

    while (n--) {
        int x; 
        cin >> x;
        if (x) 
            pq.push(x);

        else {
            if (pq.empty()) 
                cout << 0 << '\n';

            else {
                cout << pq.top() << '\n'; 
                pq.pop(); 
            }
        }
    }
    
    return 0;
}
