#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;

    unordered_set<string> unheard;
    vector<string> res;

    for (int i = 0; i < n; i++) {
        string name;
        cin >> name;
        unheard.insert(name);
    }

    for (int i = 0; i < m; i++) {
        string name;
        cin >> name;
        if (unheard.count(name)) {
            res.push_back(name);
        }
    }

    sort(res.begin(), res.end());

    cout << res.size() << '\n';

    for (const string& name : res) {
        cout << name << '\n';
    }

    return 0;
}
