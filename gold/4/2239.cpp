#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<vector<int>> board(9, vector<int>(9));
vector<pair<int, int>> blanks;

bool chk(int r, int c, int num) {
    for (int i = 0; i < 9; i++) {
        if (board[r][i] == num || board[i][c] == num) return false;
    }
    
    int sr = (r / 3) * 3, sc = (c / 3) * 3;
    for (int i = sr; i < sr + 3; i++) {
        for (int j = sc; j < sc + 3; j++) {
            if (board[i][j] == num) return false;
        }
    }
    return true;
}

bool solve(int idx) {
    if (idx == blanks.size()) return true;
    
    int r = blanks[idx].first, c = blanks[idx].second;
    
    for (int num = 1; num <= 9; num++) {
        if (chk(r, c, num)) {
            board[r][c] = num;
            if (solve(idx + 1)) return true;
            board[r][c] = 0;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    for (int i = 0; i < 9; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < 9; j++) {
            board[i][j] = s[j] - '0';
            if (board[i][j] == 0) {
                blanks.push_back({i, j});
            }
        }
    }
    
    solve(0);
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << board[i][j];
        }
        cout << "\n";
    }
    
    return 0;
}
