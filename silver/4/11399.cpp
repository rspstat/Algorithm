#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<int> times(n);
    for (int i = 0; i < n; i++) {
        cin >> times[i];
    }

    sort(times.begin(), times.end());

    int total = 0, sum = 0;
    for (int i = 0; i < n; i++) {
        sum += times[i];
        total += sum;
    }

    cout << total << endl;
    return 0;
}
