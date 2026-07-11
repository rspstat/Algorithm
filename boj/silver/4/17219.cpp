#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    unordered_map<string, string> u_map;

    string site, pw;

    int n, k;

    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        cin >> site >> pw;
        u_map[site] = pw;
    }

    for (int i = 0; i < k; i++) {
        cin >> site;
        cout << u_map[site] << "\n";
    }

    return 0;
}
