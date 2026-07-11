#include <iostream>
#include <algorithm>

using namespace std;

// 최대 쿼리 20만 * 30비트 = 약 600만 노드 필요
const int MAX = 6000005;

struct Node {
    int ch[2];
    int cnt;
} trie[MAX];

int root = 1;
int node_idx = 1;

void ins(int x) {
    int cur = root;
    trie[cur].cnt++;
    for (int i = 29; i >= 0; i--) {
        int b = (x >> i) & 1;
        if (!trie[cur].ch[b]) trie[cur].ch[b] = ++node_idx;
        cur = trie[cur].ch[b];
        trie[cur].cnt++;
    }
}

void del(int x) {
    int cur = root;
    trie[cur].cnt--;
    for (int i = 29; i >= 0; i--) {
        int b = (x >> i) & 1;
        cur = trie[cur].ch[b];
        trie[cur].cnt--;
    }
}

int qry(int x) {
    int cur = root;
    int ret = 0;
    for (int i = 29; i >= 0; i--) {
        int b = (x >> i) & 1;
        int t = 1 - b; // XOR을 최대화하기 위해 반대 비트를 찾음
        
        // 반대 비트로 가는 경로가 존재하고, 지워지지 않은 수가 있다면 이동
        if (trie[cur].ch[t] && trie[trie[cur].ch[t]].cnt > 0) {
            ret += (1 << i);
            cur = trie[cur].ch[t];
        } else {
            // 없으면 어쩔 수 없이 같은 비트로 이동 (XOR 값 0)
            cur = trie[cur].ch[b];
        }
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // 초기 상태에 0이 들어있음
    ins(0);

    int m;
    cin >> m;
    while (m--) {
        int op, x;
        cin >> op >> x;
        if (op == 1) ins(x);
        else if (op == 2) del(x);
        else cout << qry(x) << '\n';
    }

    return 0;
}
