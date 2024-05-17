#include <iostream>
#include <algorithm>
#include <vector>

#define ll long long

using namespace std;

int n = 0, m = 0;
vector<int> tree;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n >> m;

    for ( ll i = 0; i < n; i++) {
        int x;
        cin >> x;
        tree.push_back(x);
    }

    int start = 0, result = 0;
    int end = *max_element(tree.begin(), tree.end());

    while (start <= end) {
        ll int total = 0;
        int mid = (start + end) / 2;

        for (ll i = 0; i < n; i++) 
            if (tree[i] > mid) 
                total += tree[i] - mid;

        if ( total < m )
            end = mid - 1;

        else {
            result = mid;
            start = mid + 1; 
        }
    }

    cout << result;

    return 0;
}
