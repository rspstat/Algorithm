#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

const int MAX_P = 3000001;
int g[MAX_P];
vector<int> fib;

void precomputeFib() {
    fib.push_back(1);
    fib.push_back(2);
    
    while (true) {
        int next_val = fib.back() + fib[fib.size() - 2];
        if (next_val > MAX_P) break;
        fib.push_back(next_val);
    }
}

void precomputeGrundy() {
    for (int i = 1; i < MAX_P; ++i) {
        bitset<32> visited;
        
        for (int f : fib) {
            if (f > i) break;
            visited[g[i - f]] = 1;
        }
        
        int mex = 0;
        while (visited[mex]) {
            mex++;
        }
        g[i] = mex;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    precomputeFib();
    precomputeGrundy();
    
    int n;
    cin >> n;
    
    int result = 0;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        result ^= g[p];
    }
    
    if (result != 0) {
        cout << "koosaga" << "\n";
    } else {
        cout << "cubelover" << "\n";
    }
    
    return 0;
}
