#include <iostream>
#include <bits/stdc++.h>

using namespace std;

#define MAX 9

int n, m;
int f[MAX];
int arr[MAX];
bool visited[MAX];

void dfs(int num, int k) {
    if (k == m) { 
        for (int i = 0; i < m; i++)
            cout << arr[i] << " ";

        cout << "\n";
    } 

    else {
        for ( auto i = 1; i <= n; i++) {
            if (!visited[i]) {
                visited[i] = true;
                arr[k] = f[i - 1];
                dfs(i+1, k+1);
                visited[i] = false;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> f[i];
    }

    sort(f, f+n);

    dfs(1,0);

    return 0; 
}
