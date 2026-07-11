#include <bits/stdc++.h>

using namespace std;

int n, k;

// from : 출발, aux : 보조, to : 목표
void hanoi (int m, int from, int to, int aux) {
    if (m == 0) 
        return;

    hanoi(m - 1, from, aux, to);
    cout << from << " " << to << "\n";
    hanoi(m - 1, aux, to, from);
}

void solve() {
    cin >> n;
    // 점화식 : a[n+1] = 2 * a[n] - 1, 이동 횟수 : 2 ^ n - 1
    cout << (1LL << n) - 1 << "\n";  
    hanoi(n, 1, 3, 2);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    solve();
    
    return 0;
}
