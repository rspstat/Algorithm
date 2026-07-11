#include <iostream>

using namespace std;

int main()
{
    int a, b, c, d, e, f = 0;

    cin >> a >> b;

    c = a * (b % 10); //1의자리
    cout << c << endl;

    d = a * ((b % 100) / 10);    //10의 자리
    cout << d << endl;

    e = (a * (b / 100));       //100의 자리
    cout << e << endl;

    f = a * b;      //전체 출력
    cout << f << endl;

    return 0;
}
