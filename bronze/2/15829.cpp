#define ll long long
#include <iostream>
#include <string>

using namespace std;

ll M = 1234567891;

int main() { 
    int n = 0; 
    ll r = 1;
    ll hash = 0;
    string str;

    cin >> n;
    cin >> str;

    for (int i = 0; i < n; i++) {
        hash = (hash + (str[i] - 'a' + 1) * r) % M;     //+=, *= 쓰면 안되고 풀어서 써야함
        r = (r * 31) % M;
    }

    cout << hash;

    return 0;
}
