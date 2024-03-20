#include <iostream>

using namespace std;

int main() {

    int a[8] = {0,};
    int temp = 0;

    for (int i = 0; i < 8; i++)
        cin >> a[i];

    if (a[0] == 1) {
        for (int j = 1; j < 8; j++) {
            if (a[j] == j+1) 
                temp--;
        }
    }

    else if (a[0] == 8) {
        for (int c = 1; c < 8; c++) {
            if ( a[c] == 8 - c ) 
                temp++;
        }
    }

    if ( temp == 7 )
        cout << "descending" << endl;

    else if ( temp == -7 )
        cout << "ascending" << endl;

    else 
        cout << "mixed" << endl;
    
    
    

    return 0;
}
