#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct St {
    bool ok;
    string a;
    string b;
    string c;

    St() : ok(false) {}
    St(string a_, string b_, string c_) : ok(true), a(std::move(a_)), b(std::move(b_)), c(std::move(c_)) {}
};

bool better(const St &x, const St &y) {
    if (!y.ok) return true;
    if (!x.ok) return false;

    if (x.a != y.a) return x.a < y.a;
    if (x.b != y.b) return x.b < y.b;
    return x.c < y.c;
}

vector<int> alw(const string &s, int i, int l, int st) {
    if (i < st) return { 0 };

    char ch = s[i - st];

    if (ch != '?') {
        int d = ch - '0';
        return { d };
    }

    vector<int> r;
    r.reserve(10);

    if (l > 1 && i == st) {
        for (int d = 1; d <= 9; d++) r.push_back(d);
    } else {
        for (int d = 0; d <= 9; d++) r.push_back(d);
    }

    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    string line;
    getline(cin, line);

    for (int tc = 1; tc <= t; tc++) {
        getline(cin, line);

        int p1 = (int)line.find(' ');
        int p2 = (int)line.find(' ', p1 + 1);
        int p3 = (int)line.find(' ', p2 + 1);
        int p4 = (int)line.find(' ', p3 + 1);

        string sa = line.substr(0, p1);
        char op = line[p1 + 1];
        string sb = line.substr(p2 + 1, p3 - (p2 + 1));
        string sc = line.substr(p4 + 1);

        int la = (int)sa.size();
        int lb = (int)sb.size();
        int lc = (int)sc.size();

        int l = max(la, max(lb, lc));
        int sta = l - la;
        int stb = l - lb;
        int stc = l - lc;

        bool bad = false;

        if (la > 1) {
            if (sa[0] == '0') bad = true;
        }
        if (lb > 1) {
            if (sb[0] == '0') bad = true;
        }
        if (lc > 1) {
            if (sc[0] == '0') bad = true;
        }

        vector<vector<St>> dp(l + 1, vector<St>(2));

        if (!bad) dp[0][0] = St("", "", "");

        for (int i = 0; i < l; i++) {
            for (int cur = 0; cur <= 1; cur++) {
                if (!dp[i][cur].ok) continue;

                vector<int> da = alw(sa, i, la, sta);
                vector<int> db = alw(sb, i, lb, stb);
                vector<int> dc = alw(sc, i, lc, stc);

                for (int a : da) {
                    for (int b : db) {
                        for (int c : dc) {
                            int nxt;

                            if (op == '+') {
                                int v = c + 10 * cur - a - b;
                                if (v < 0 || v > 1) continue;
                                nxt = v;
                            } else {
                                int v = a - b + 10 * cur - c;
                                if (v < 0 || v > 1) continue;
                                nxt = v;
                            }

                            if (i == l - 1 && nxt != 0) continue;

                            string na = dp[i][cur].a;
                            string nb = dp[i][cur].b;
                            string nc = dp[i][cur].c;

                            if (i >= sta) na.push_back((char)('0' + a));
                            if (i >= stb) nb.push_back((char)('0' + b));
                            if (i >= stc) nc.push_back((char)('0' + c));

                            St cand(std::move(na), std::move(nb), std::move(nc));

                            if (better(cand, dp[i + 1][nxt])) dp[i + 1][nxt] = std::move(cand);
                        }
                    }
                }
            }
        }

        cout << "Case #" << tc << ": ";

        if (!dp[l][0].ok) {
            cout << "IMPOSSIBLE\n";
            continue;
        }

        string ra = dp[l][0].a;
        string rb = dp[l][0].b;
        string rc = dp[l][0].c;

        cout << ra << ' ' << op << ' ' << rb << " = " << rc << "\n";
    }

    return 0;
}
