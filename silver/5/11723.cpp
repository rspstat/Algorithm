#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int m;
    cin >> m;

    int bitset = 0; // 비트마스크로 집합 표현

    while (m--) {
        string str;
        int x;

        cin >> str;

        if ( str == "add" ) {       // 여기서 문자열 먼저 받고 if 문 안에서 뒤 숫자 받는 skill 필요
            cin >> x;
            bitset |= (1 << (x - 1));   // |= 특정 비트를 키는(1로 설정) 역할
        }
        
        else if (str == "remove") {
            cin >> x;
            bitset &= ~(1 << (x - 1));  // AND
        } 
       
        else if (str == "check") {
            cin >> x;
            cout << ((bitset & (1 << (x - 1))) ? 1 : 0) << '\n';
        } 
        
        else if (str == "toggle") {
            cin >> x;
            bitset ^= (1 << (x - 1));   // XOR 
        } 
        
        else if (str == "all") {
            bitset = (1 << 20) - 1;
        } 
        
        else if (str == "empty") {
            bitset = 0;
        }
    }

    return 0;
}
