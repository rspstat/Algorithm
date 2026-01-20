#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

const int MAX = 400005;

struct Query {
    int x, y, id;
};

struct Point {
    int val, pos;
};

int P[MAX];
int bit[MAX];
long long ans[100005];

void update(int idx, int val, int n) {
    for (; idx <= n; idx += idx & -idx)
        bit[idx] += val;
}

int query(int idx) {
    int sum = 0;
    for (; idx > 0; idx -= idx & -idx)
        sum += bit[idx];
    return sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;

    string t = "#";
    for (char c : s) {
        t += c;
        t += "#";
    }

    int n = t.length();
    int r = 0, c = 0;
    for (int i = 0; i < n; i++) {
        if (i < r)
            P[i] = min(P[2 * c - i], r - i);
        else
            P[i] = 0;

        while (i - P[i] - 1 >= 0 && i + P[i] + 1 < n && t[i - P[i] - 1] == t[i + P[i] + 1])
            P[i]++;

        if (i + P[i] > r) {
            r = i + P[i];
            c = i;
        }
    }

    vector<Point> points;
    for (int i = 0; i < n; i++) {
        points.push_back({i - P[i], i});
    }

    int m;
    cin >> m;
    vector<Query> queries(m);
    for (int i = 0; i < m; i++) {
        int idx, len;
        cin >> idx >> len;
        queries[i] = {2 * idx, 2 * idx + len, i};
    }

    sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
        return a.val < b.val;
    });

    sort(queries.begin(), queries.end(), [](const Query& a, const Query& b) {
        return a.x < b.x;
    });

    int p_idx = 0;
    int total_points = 0;
    int bit_limit = MAX - 1;

    for (int i = 0; i < m; i++) {
        while (p_idx < points.size() && points[p_idx].val <= queries[i].x) {
            update(points[p_idx].pos + 1, 1, bit_limit);
            total_points++;
            p_idx++;
        }
        
        int y_idx = min(queries[i].y, bit_limit);
        ans[queries[i].id] = total_points - query(y_idx);
    }

    for (int i = 0; i < m; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}
