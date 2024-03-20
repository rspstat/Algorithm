#include <iostream>

using namespace std;

int main()
{
    int n = 0;
    cin >> n;
    int temp = 1;

    if (n == 0) {
        cout << "1" << endl;
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        temp = temp * i;
    }

    cout << temp;



    return 0;
}
