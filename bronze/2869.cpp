#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int a, b, v, cnt = 0;

    cin >> a >> b >> v;

    int day = 1;
    day += (v-a) / (a-b);

    if ( (v-a) % (a-b) != 0 )
        day++;
    

    if ( a >= v ) 
        cout << '1' << '\n';
    

    else 
        cout << day << '\n';

    return 0;
}
