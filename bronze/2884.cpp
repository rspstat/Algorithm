#include <iostream>

using namespace std;

int main()
{
    int H, M = 0;

    cin >> H >> M;

    if ((!(H == 0) && 0 <= M && M < 45)) {

        cout << H - 1 << " " << M + 15 << endl;

    }
    
    if ((H == 0) && ( 0 <= M && M < 45)) {

        cout << 23 << " " << M + 15 << endl;

    }

    if ( 60 > M && M >= 45 ) {
        cout << H << " " << M - 45 << endl;
    }

    return 0;
}
