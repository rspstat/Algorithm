#include <iostream>

using namespace std;

int main() {

    int n, m = 0;

    cin >> n >> m;

    int mat[n][m];
    int mat2[n][m];
    int res[n][m];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mat[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mat2[i][j];
        }
    }
    

    for (int ccc = 0; ccc < n; ccc++) {
        for (int cc = 0; cc < m; cc++) {
            res[ccc][cc] = mat[ccc][cc] + mat2[ccc][cc];
        }
    }

    for (int qq = 0; qq < n; qq++) {
        for (int pp = 0; pp < m; pp++) {
            cout << res[qq][pp] << " ";
        }

        cout << endl;
    }

    cout << endl;


    return 0;
}
