#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    vector<pair<long long, long long>> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i].first >> p[i].second;
    }
    
    long long area = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += p[i].first * p[j].second - p[j].first * p[i].second;
    }
    
    area = abs(area);
    
    cout << area / 2;
    if (area % 2 == 1) {
        cout << ".5";
    } else {
        cout << ".0";
    }
    cout << "\n";
    
    return 0;
}
