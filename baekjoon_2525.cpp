#include <iostream>

using namespace std;

int main()
{
    int h, m, c, temp = 0;

    cin >> h >> m;  //현재 시간과 분
    cin >> c;       //돌려야되는 분

    temp = m + c;   //현재 분과 돌려야되는 분을 더함.

    if ( 1000 >= c && c >= 0 )
        h += ( temp / 60 ); // temp를 60으로 나눈 몫만큼 시간에 더함

    if ( h >= 24 ) //24시를 넘으면 다시 0시부터 계산
    h -= 24;

    if ( temp < 60 )
        cout << h << " " << temp << endl;

    else if ( temp > 60 ) {
        c %= 60;
        cout << h << " " << (temp % 60) << endl; 
    }

    else if ( temp == 60 ) 
        cout << h << " " << 0 << endl; 

    return 0;
}
