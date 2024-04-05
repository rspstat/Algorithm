#include <iostream>

using namespace std;

long long pow_mod(long long a, long long b, long long c);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    long long A, B, C;
    cin >> A >> B >> C;
    cout << pow_mod(A, B, C);
    
    return 0;
}

long long pow_mod(long long a, long long b, long long c) {  //분할 정복
    if (b == 0)      //a^0 = 1
        return 1;  
    
    if (b % 2 == 1) {   //지수 홀수
        long long part1 = a % c;
        long long part2 = pow_mod(a, b-1, c);
        return (part1 * part2) % c;

    } 
    
    else {    //지수 짝수
        long long half = pow_mod(a, b/2, c);
        return (half * half) % c;
    }
}
