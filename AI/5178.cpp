#include <bits/stdc++.h>
using namespace std;

static inline __int128 cross3(long long ax, long long ay, long long bx, long long by, long long cx, long long cy) {
    __int128 x1 = (__int128)(bx - ax);
    __int128 y1 = (__int128)(by - ay);
    __int128 x2 = (__int128)(cx - bx);
    __int128 y2 = (__int128)(cy - by);
    return x1 * y2 - y1 * x2;
}

static inline void normalize(vector<pair<int,int>>& v) {
    if (v.empty()) return;

    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    vector<pair<int,int>> tmp;
    tmp.reserve(v.size());
    for (int i = 0; i < (int)v.size(); ) {
        int a = v[i].first;
        int bestb = v[i].second;
        int j = i + 1;
        while (j < (int)v.size() && v[j].first == a) {
            bestb = max(bestb, v[j].second);
            j++;
        }
        tmp.push_back({a, bestb});
        i = j;
    }
    v.swap(tmp);

    sort(v.begin(), v.end(), [&](auto& p, auto& q){
        if (p.first != q.first) return p.first > q.first;
        return p.second > q.second;
    });

    vector<pair<int,int>> pareto;
    pareto.reserve(v.size());
    int maxB = -1;
    for (auto &t : v) {
        if (t.second > maxB) {
            pareto.push_back(t);
            maxB = t.second;
        }
    }

    sort(pareto.begin(), pareto.end(), [&](auto& p, auto& q){
        if (p.first != q.first) return p.first < q.first;
        return p.second > q.second;
    });

    vector<pair<int,int>> hull;
    hull.reserve(pareto.size());
    for (auto &pt : pareto) {
        while (hull.size() >= 2) {
            auto a = hull[hull.size()-2];
            auto b = hull[hull.size()-1];
            auto c = pt;
            __int128 cr = cross3(a.first, a.second, b.first, b.second, c.first, c.second);
            if (cr >= 0) hull.pop_back();
            else break;
        }
        hull.push_back(pt);
    }

    v.swap(hull);
}

static inline void mergeInto(vector<pair<int,int>>& a, const vector<pair<int,int>>& b) {
    if (b.empty()) return;
    a.insert(a.end(), b.begin(), b.end());
    normalize(a);
}

static inline vector<pair<int,int>> shifted(const vector<pair<int,int>>& v, int dx, int dy) {
    vector<pair<int,int>> r;
    r.reserve(v.size());
    for (auto &t : v) r.push_back({t.first + dx, t.second + dy});
    normalize(r);
    return r;
}

static string termToString(int x, int y) {
    if (x == 0 && y == 0) return "1";
    string s;
    if (x > 0) {
        s += "x";
        if (x > 1) s += "^" + to_string(x);
    }
    if (y > 0) {
        s += "y";
        if (y > 1) s += "^" + to_string(y);
    }
    return s;
}

struct Frame {
    char arg;
    vector<pair<int,int>> poly;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    string line;
    getline(cin, line);

    for (int tc = 1; tc <= K; tc++) {
        while (true) {
            if (!getline(cin, line)) line.clear();
            if (!line.empty()) break;
        }

        vector<Frame> st;
        st.push_back(Frame{0, {}});

        auto isDigits = [&](const string& s) -> bool {
            if (s.empty()) return false;
            for (char c : s) if (c < '0' || c > '9') return false;
            return true;
        };

        while (true) {
            if (line == "basic") {
                st.back().poly.push_back({0, 0});
                normalize(st.back().poly);
            } else if (line.rfind("loop ", 0) == 0) {
                string a = line.substr(5);
                char arg = 'n';
                if (a == "x") arg = 'x';
                else if (a == "y") arg = 'y';
                else if (isDigits(a)) arg = 'n';
                st.push_back(Frame{arg, {}});
            } else if (line == "endloop") {
                Frame body = st.back();
                st.pop_back();

                if (!body.poly.empty()) {
                    int dx = (body.arg == 'x') ? 1 : 0;
                    int dy = (body.arg == 'y') ? 1 : 0;
                    auto p2 = shifted(body.poly, dx, dy);
                    mergeInto(st.back().poly, p2);
                }
            } else if (line == "endprogram") {
                break;
            }

            if (!getline(cin, line)) line = "endprogram";
        }

        vector<pair<int,int>> poly = st.back().poly;
        normalize(poly);

        cout << "Data Set " << tc << ":\n";

        if (poly.empty()) {
            cout << "0\n";
        } else if (poly.size() == 1 && poly[0].first == 0 && poly[0].second == 0) {
            cout << "1\n";
        } else {
            sort(poly.begin(), poly.end(), [&](auto& a, auto& b){
                if (a.first != b.first) return a.first > b.first;
                return a.second > b.second;
            });

            for (int i = 0; i < (int)poly.size(); i++) {
                if (i) cout << " + ";
                cout << termToString(poly[i].first, poly[i].second);
            }
            cout << "\n";
        }

        if (tc != K) cout << "\n";
    }

    return 0;
}
