#include <bits/stdc++.h>
using namespace std;

int prec(char op) {
    if (op == '(') return 0;
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return -1;
}

void solve() {
    string s;
    cin >> s;
    stack<char> st;
    ostringstream out;

    for (char c : s) {
        if (isalpha(c)) {
            out << c;
        } else if (c == '(') {
            st.push(c);
        } else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                out << st.top();
                st.pop();
            }
            if (!st.empty()) st.pop();
        } else { // 연산자
            while (!st.empty() && prec(st.top()) >= prec(c)) {
                out << st.top();
                st.pop();
            }
            st.push(c);
        }
    }
    while (!st.empty()) {
        out << st.top();
        st.pop();
    }
    cout << out.str() << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
