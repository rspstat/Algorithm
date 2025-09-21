#include <bits/stdc++.h>
using namespace std;

int n;

void preorder(int u, const vector<int>& L, const vector<int>& R, ostringstream& out) {
    if (u == -1) return;
    out << char('A' + u);
    preorder(L[u], L, R, out);
    preorder(R[u], L, R, out);
}

void inorder(int u, const vector<int>& L, const vector<int>& R, ostringstream& out) {
    if (u == -1) return;
    inorder(L[u], L, R, out);
    out << char('A' + u);
    inorder(R[u], L, R, out);
}

void postorder(int u, const vector<int>& L, const vector<int>& R, ostringstream& out) {
    if (u == -1) return;
    postorder(L[u], L, R, out);
    postorder(R[u], L, R, out);
    out << char('A' + u);
}

void solve() {
    cin >> n;
    vector<int> L(26, -1), R(26, -1);
    for (int i = 0; i < n; ++i) {
        char p, l, r;
        cin >> p >> l >> r;
        int u = p - 'A';
        L[u] = (l == '.') ? -1 : (l - 'A');
        R[u] = (r == '.') ? -1 : (r - 'A');
    }

    ostringstream out;
    preorder(0, L, R, out);   out << '\n';   // 루트는 'A' (0)
    inorder(0, L, R, out);    out << '\n';
    postorder(0, L, R, out);  out << '\n';

    cout << out.str();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
