#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cstring>

using namespace std;

const int MAXN = 2000 * 2000 + 5;
int trie[MAXN][2];
int fail[MAXN];
int term[MAXN];
int nodes = 1;

int get_idx(char c) {
    return (c == 'x');
}

void ins(const string& s, int id) {
    int cur = 0;
    for (char c : s) {
        int bit = get_idx(c);
        if (!trie[cur][bit]) trie[cur][bit] = nodes++;
        cur = trie[cur][bit];
    }
    term[cur] = id;
}

void build() {
    queue<int> q;
    for (int i = 0; i < 2; i++) {
        if (trie[0][i]) q.push(trie[0][i]);
    }
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int i = 0; i < 2; i++) {
            if (trie[cur][i]) {
                int nxt = trie[cur][i];
                fail[nxt] = trie[fail[cur]][i];
                q.push(nxt);
            } else {
                trie[cur][i] = trie[fail[cur]][i];
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int hp, wp, hm, wm;
    cin >> hp >> wp >> hm >> wm;

    vector<string> p(hp);
    vector<int> p_ids(hp);
    vector<string> uniq_rows;
    memset(term, -1, sizeof(term));

    // 패턴 행 중복 제거 및 ID 부여
    for (int i = 0; i < hp; i++) {
        cin >> p[i];
        bool found = false;
        for (int j = 0; j < uniq_rows.size(); j++) {
            if (uniq_rows[j] == p[i]) {
                p_ids[i] = j;
                found = true;
                break;
            }
        }
        if (!found) {
            p_ids[i] = uniq_rows.size();
            uniq_rows.push_back(p[i]);
            ins(p[i], p_ids[i]);
        }
    }

    build();

    // 세로 매칭을 위한 KMP 실패 함수 계산
    vector<int> pi(hp, 0);
    for (int i = 1, j = 0; i < hp; i++) {
        while (j > 0 && p_ids[i] != p_ids[j]) j = pi[j - 1];
        if (p_ids[i] == p_ids[j]) j++;
        pi[i] = j;
    }

    vector<int> col_st(wm, 0);
    long long ans = 0;

    for (int i = 0; i < hm; i++) {
        string s;
        cin >> s;
        int cur = 0;
        for (int j = 0; j < wm; j++) {
            // 아호 코라식으로 현재 행에서의 패턴 매칭 확인
            cur = trie[cur][get_idx(s[j])];
            int mid = term[cur]; 

            // 각 열(Column)별로 KMP 상태 업데이트
            int k = col_st[j];
            while (k > 0 && (mid == -1 || p_ids[k] != mid)) k = pi[k - 1];
            if (mid != -1 && p_ids[k] == mid) k++;
            
            col_st[j] = k;

            if (col_st[j] == hp) {
                ans++;
                col_st[j] = pi[k - 1];
            }
        }
    }

    cout << ans << '\n';

    return 0;
}
