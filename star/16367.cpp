#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

int k, n, id, scc_cnt;
vector<int> adj[10005];
int d[10005], scc[10005];
stack<int> st;
bool fin[10005];

// x가 0보다 작거나 같으면 1-based index로 변환
// 1~k: Red(True), k+1~2k: Blue(False)
int trans(int x, char c) {
    if (c == 'R') return x;
    return x + k;
}

int not_op(int x) {
    if (x > k) return x - k;
    return x + k;
}

int dfs(int cur) {
    d[cur] = ++id;
    st.push(cur);

    int p = d[cur];
    for (int nxt : adj[cur]) {
        if (d[nxt] == 0) p = min(p, dfs(nxt));
        else if (!fin[nxt]) p = min(p, d[nxt]);
    }

    if (p == d[cur]) {
        scc_cnt++;
        while (true) {
            int t = st.top();
            st.pop();
            fin[t] = true;
            scc[t] = scc_cnt;
            if (t == cur) break;
        }
    }
    return p;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> k >> n;
    for (int i = 0; i < n; i++) {
        int l1, l2, l3;
        char c1, c2, c3;
        cin >> l1 >> c1 >> l2 >> c2 >> l3 >> c3;

        int p1 = trans(l1, c1);
        int p2 = trans(l2, c2);
        int p3 = trans(l3, c3);

        // (p1 or p2) and (p2 or p3) and (p3 or p1)
        // !p1 -> p2, !p2 -> p1
        adj[not_op(p1)].push_back(p2);
        adj[not_op(p2)].push_back(p1);

        // !p2 -> p3, !p3 -> p2
        adj[not_op(p2)].push_back(p3);
        adj[not_op(p3)].push_back(p2);

        // !p3 -> p1, !p1 -> p3
        adj[not_op(p3)].push_back(p1);
        adj[not_op(p1)].push_back(p3);
    }

    for (int i = 1; i <= 2 * k; i++) {
        if (d[i] == 0) dfs(i);
    }

    for (int i = 1; i <= k; i++) {
        if (scc[i] == scc[i + k]) {
            cout << -1;
            return 0;
        }
    }

    // SCC 번호가 작을수록 위상 정렬상 뒤에 위치 -> False
    // SCC(True) < SCC(False)이면 True
    for (int i = 1; i <= k; i++) {
        cout << (scc[i] < scc[i + k] ? 'R' : 'B');
    }

    return 0;
}
