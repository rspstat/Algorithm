#include <iostream>
#include <string>
#include <bitset>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    while (t--) {
        long long n;
        cin >> n;

        n = (n - 1) % 28;
        int target;

        if (n < 15)
            target = n + 1;

        else
            target = 28 - n + 1;

        bitset<4> res(target);
        string temp = res.to_string();

        string ans = "";
        for (char c : temp) {
            if (c == '0') ans += "V";
            else ans += "딸기";
        }

        cout << ans << "\n";
    }

    return 0;
}
