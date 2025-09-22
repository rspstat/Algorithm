#include <bits/stdc++.h>
using namespace std;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while (t--) {
        int h, w;
        cin >> h >> w;
        
        // 가장자리에 패딩 추가하여 외부에서 시작 가능하게 만듦
        vector<string> b(h + 2, string(w + 2, '.'));
        
        for (int i = 1; i <= h; i++) {
            string s;
            cin >> s;
            for (int j = 1; j <= w; j++) {
                b[i][j] = s[j - 1];
            }
        }
        
        string k;
        cin >> k;
        
        // 초기 열쇠 설정
        vector<bool> key(26, false);
        if (k != "0") {
            for (char c : k) {
                key[c - 'a'] = true;
            }
        }
        
        int ans = 0;
        bool changed = true;
        
        // 새로운 열쇠를 획득할 때마다 반복
        while (changed) {
            changed = false;
            vector<vector<bool>> v(h + 2, vector<bool>(w + 2, false));
            queue<pair<int, int>> q;
            
            q.push({0, 0});
            v[0][0] = true;
            
            while (!q.empty()) {
                auto [x, y] = q.front();
                q.pop();
                
                for (int d = 0; d < 4; d++) {
                    int nx = x + dx[d];
                    int ny = y + dy[d];
                    
                    if (nx < 0 || nx > h + 1 || ny < 0 || ny > w + 1 || v[nx][ny])
                        continue;
                    
                    char cur = b[nx][ny];
                    
                    // 벽인 경우
                    if (cur == '*') continue;
                    
                    // 문인 경우
                    if (cur >= 'A' && cur <= 'Z') {
                        if (!key[cur - 'A']) continue;
                    }
                    
                    v[nx][ny] = true;
                    q.push({nx, ny});
                    
                    // 열쇠 발견
                    if (cur >= 'a' && cur <= 'z') {
                        if (!key[cur - 'a']) {
                            key[cur - 'a'] = true;
                            changed = true;
                        }
                    }
                    
                    // 문서 발견
                    if (cur == '$') {
                        ans++;
                        b[nx][ny] = '.';  // 문서는 한 번만 획득
                    }
                }
            }
        }
        
        cout << ans << '\n';
    }
    
    return 0;
}
