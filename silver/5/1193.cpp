#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int X = 0;
    cin >> X;

    int i = 1;

    while ( X > i ) {
        X -= i;
        i++;
    }

    //i에 몇 번째 대각선인지 담겨있다.

    if ( i % 2 == 0 )  //짝수일때
        cout << X << "/" << i - X + 1;
    
    else  //홀수일때
        cout << i - X + 1 << "/" << X;
    
    return 0;
}   
