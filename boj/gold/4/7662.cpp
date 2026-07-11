#include <bits/stdc++.h>

using namespace std;

int k;

void solve() {

    cin >> k;

    multiset<int> ms;

    for (int i = 0; i < k; ++i) {
        char cmd;
        int n;

        cin >> cmd >> n;
        
        if (cmd == 'I') {
            ms.insert(n);
        } 
        
        else {
            if (ms.empty()) {   // cmd == 'D' 큐가 비어있는데 적용할 연산이 D인 경우
                continue;
            }

            if (n == 1) {  // 최댓값 삭제
                ms.erase(prev(ms.end()));   // multiset에서 end 값은 꼭 prev()로 접근해야함.
            }

            else {  // n == -1, 최솟값 삭제
                ms.erase(ms.begin());
            }
        }
    }

    if (ms.empty()) {
        cout << "EMPTY\n";
    } 
    
    else {
        cout << *ms.rbegin() << " " << *ms.begin() << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; ++i) {
        solve();
    }

    return 0;
}
