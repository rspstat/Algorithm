#include <iostream>

using namespace std;

int main() {

    int mat[9][9];

    for (int h = 0; h < 9; h++) {
        for (int l = 0; l < 9; l++) {
            cin >> mat[h][l];
        }
    }

    int res, max = 0;
    int index, index2 = 0;
    max = mat[0][0];

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if ( max <= mat[i][j] ) {
                max = mat[i][j];
                index = i+1;
                index2 = j+1;
            }
        }
    }
    
    cout << max << endl;
    cout << index << " " << index2 << endl;



    return 0;
}
