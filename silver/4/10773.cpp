#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int k, tmp, sum = 0;
    cin >> k;

    stack<int> s;

    for (int i = 0; i < k; i++) {
        cin >> tmp;
        if ( tmp == 0 )
            s.pop();
        
        else 
            s.push(tmp); 
    }

    while(!s.empty()) {
        sum+=s.top();
        s.pop();
    }

    cout << sum << "\n";

    return 0;
}
