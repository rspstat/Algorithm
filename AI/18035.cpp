#include <bits/stdc++.h>
using namespace std;

struct SAM {
    struct State {
        int next[26];
        int link;
        int len;
        State() : link(-1), len(0) { fill(next, next + 26, -1); }
    };

    vector<State> st;
    int last;

    SAM(int max_len = 0) {
        st.reserve(2 * max_len + 1);
        st.push_back(State());
        st[0].link = -1;
        st[0].len = 0;
        last = 0;
    }

    void extend(int c) {
        int cur = (int)st.size();
        st.push_back(State());
        st[cur].len = st[last].len + 1;

        int p = last;
        while (p != -1 && st[p].next[c] == -1) {
            st[p].next[c] = cur;
            p = st[p].link;
        }

        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = (int)st.size();
                st.push_back(st[q]);
                st[clone].len = st[p].len + 1;

                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }

        last = cur;
    }

    void build(const string& s) {
        for (char ch : s) extend(ch - 'A');
    }

    int min_pictures(const string& s) const {
        int n = (int)s.size();
        vector<int> best(n, 0);

        int v = 0, l = 0;
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'A';
            if (st[v].next[c] != -1) {
                v = st[v].next[c];
                l++;
            } else {
                while (v != -1 && st[v].next[c] == -1) v = st[v].link;
                if (v == -1) {
                    v = 0;
                    l = 0;
                } else {
                    l = st[v].len;
                    v = st[v].next[c];
                    l++;
                }
            }
            if (l > 0) {
                int start = i - l + 1;
                if (best[start] < l) best[start] = l;
            }
        }

        for (int i = 0; i + 1 < n; i++) {
            int cand = best[i] - 1;
            if (cand > best[i + 1]) best[i + 1] = cand;
        }

        int jumps = 0, curEnd = 0, curFar = 0;
        for (int i = 0; i < n; i++) {
            if (i > curFar) return -1;
            curFar = max(curFar, i + best[i]);
            if (i == curEnd) {
                jumps++;
                curEnd = curFar;
                if (curEnd >= n) break;
            }
        }
        return (curEnd >= n) ? jumps : -1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string C;
    cin >> C;
    int N;
    cin >> N;

    SAM sam((int)C.size());
    sam.build(C);

    while (N--) {
        string s;
        cin >> s;
        cout << sam.min_pictures(s) << "\n";
    }
    return 0;
}
