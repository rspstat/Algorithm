#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<string> board;
vector<vector<int>> group_id;
vector<int> group_size;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void bfs(int sx, int sy, int gid) {
    queue<pair<int, int>> q;
    q.push({sx, sy});
    group_id[sx][sy] = gid;
    int cnt = 1;
    
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (board[nx][ny] == '1' || group_id[nx][ny] != -1) continue;
            
            group_id[nx][ny] = gid;
            q.push({nx, ny});
            cnt++;
        }
    }
    
    group_size[gid] = cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m;
    board.resize(n);
    group_id.assign(n, vector<int>(m, -1));
    
    for (int i = 0; i < n; i++) {
        cin >> board[i];
    }
    
    int gid = 0;
    
    // 빈 공간들을 그룹핑
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] == '0' && group_id[i][j] == -1) {
                group_size.push_back(0);
                bfs(i, j, gid++);
            }
        }
    }
    
    // 각 벽에 대해 답 계산
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] == '1') {
                set<int> adjacent_groups;
                
                // 인접한 빈 공간 그룹들 찾기
                for (int d = 0; d < 4; d++) {
                    int ni = i + dx[d];
                    int nj = j + dy[d];
                    
                    if (ni >= 0 && ni < n && nj >= 0 && nj < m && 
                        board[ni][nj] == '0') {
                        adjacent_groups.insert(group_id[ni][nj]);
                    }
                }
                
                // 벽을 부쉈을 때 이동 가능한 칸 수 계산
                int result = 1; // 벽을 부순 자리
                for (int g : adjacent_groups) {
                    result += group_size[g];
                }
                
                cout << result % 10;
            } else {
                cout << 0;
            }
        }
        cout << '\n';
    }
    
    return 0;
}
