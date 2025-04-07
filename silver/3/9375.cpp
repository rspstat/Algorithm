#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t, n;
    string a, b;

    cin >> t;

    while (t--) {
        map<string, int> mp;

        cin >> n;

        for (int i = 0; i < n; i++) {
            cin >> a >> b;

            // headgear가 2개, eyeglasses가 1개면 map 2번째 카운트에 그 항목에 ++
            mp[b]++;    
        }

        long long ret = 1;

        // 여기가 핵심인데, 같은 항목의 부위들은 + 1을 해주고 계속 곱해줘야함.
        for (auto a : mp) {
            ret *= ((long long)a.second + 1);
        }

        ret--;

        cout << ret << "\n";
    }

    return 0;
}
