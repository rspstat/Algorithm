#include <bits/stdc++.h>
using namespace std;

struct Node {
    int ch[2];
    int depth;
    int need;
    unsigned char st;
    Node() : depth(0), need(0), st(0) { ch[0] = ch[1] = -1; }
};

static const unsigned char FREE_ = 0;
static const unsigned char INUSE_ = 1;
static const unsigned char BLOCK_ = 2;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<Node> tr;
    tr.reserve(2500000);
    tr.push_back(Node());

    auto get_child = [&](int v, int b) -> int {
        int &to = tr[v].ch[b];
        if (to == -1) {
            to = (int)tr.size();
            tr.push_back(Node());
            tr[to].depth = tr[v].depth + 1;
        }
        return to;
    };

    vector<int> need;
    need.reserve(N);

    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        int v = 0;
        for (char c : s) {
            int b = c - '0';
            tr[v].st = BLOCK_;
            v = get_child(v, b);
        }
        if (tr[v].need == 0) need.push_back(v);
        tr[v].need++;
    }

    sort(need.begin(), need.end(), [&](int a, int b) { return tr[a].depth > tr[b].depth; });

    long long ans = 0;

    queue<int> q, ex;

    for (int src : need) {
        while (!q.empty()) q.pop();
        while (!ex.empty()) ex.pop();
        q.push(src);

        while (tr[src].need > 0) {
            if (!ex.empty() && (q.empty() || tr[ex.front()].depth + 2 <= tr[q.front()].depth)) {
                int v = ex.front(); ex.pop();
                tr[src].need--;
                tr[v].st = BLOCK_;
                ans += (long long)tr[v].depth - tr[src].depth + 2;

                for (int b = 0; b < 2; b++) {
                    int to = get_child(v, b);
                    tr[to].st = INUSE_;
                    ex.push(to);
                }
            } else {
                int v = q.front(); q.pop();

                if (tr[v].st == FREE_) {
                    tr[src].need--;
                    tr[v].st = INUSE_;
                    ans += (long long)tr[v].depth - tr[src].depth;
                }

                if (tr[v].st == BLOCK_) {
                    q.push(get_child(v, 0));
                    q.push(get_child(v, 1));
                } else {
                    ex.push(v);
                }
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
