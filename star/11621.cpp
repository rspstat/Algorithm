#include <bits/stdc++.h>
using namespace std;

static inline int parse_r10(const string& s) {
    int a = 0, b = 0;
    size_t p = s.find('.');
    if (p == string::npos) {
        a = stoi(s);
        b = 0;
    } else {
        a = stoi(s.substr(0, p));
        b = (p + 1 < s.size() ? (s[p + 1] - '0') : 0);
    }
    return a * 10 + b;
}

static inline bool seg_intersects_circle_scaled(
    long long ax, long long ay, long long bx, long long by,
    long long cx, long long cy, long long r10
) {
    long double dx = (long double)(bx - ax);
    long double dy = (long double)(by - ay);
    long double px = (long double)(cx - ax);
    long double py = (long double)(cy - ay);

    long double len2 = dx * dx + dy * dy;
    long double t = 0.0L;
    if (len2 > 0) t = (px * dx + py * dy) / len2;
    if (t < 0.0L) t = 0.0L;
    else if (t > 1.0L) t = 1.0L;

    long double qx = (long double)ax + t * dx;
    long double qy = (long double)ay + t * dy;

    long double ex = (long double)cx - qx;
    long double ey = (long double)cy - qy;

    long double dist2 = ex * ex + ey * ey;
    long double rr = (long double)r10 * (long double)r10;

    return dist2 < rr;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    static int idx_at[501][501];
    for (int i = 0; i <= 500; ++i) for (int j = 0; j <= 500; ++j) idx_at[i][j] = -1;

    vector<int> cx(n), cy(n), r10(n);

    for (int i = 0; i < n; ++i) {
        int x, y;
        string rs;
        cin >> x >> y >> rs;
        cx[i] = x;
        cy[i] = y;
        r10[i] = parse_r10(rs);
        idx_at[x][y] = i;
    }

    int q;
    cin >> q;

    static int stamp[501][501];
    for (int i = 0; i <= 500; ++i) for (int j = 0; j <= 500; ++j) stamp[i][j] = 0;

    for (int qi = 1; qi <= q; ++qi) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        long long ax = (long long)x1 * 10;
        long long ay = (long long)y1 * 10;
        long long bx = (long long)x2 * 10;
        long long by = (long long)y2 * 10;

        int gx = x1, gy = y1;
        int gx_end = x2, gy_end = y2;

        long long dx = bx - ax;
        long long dy = by - ay;

        int stepX = (dx > 0) - (dx < 0);
        int stepY = (dy > 0) - (dy < 0);

        long double tMaxX, tMaxY, tDeltaX, tDeltaY;

        const long double INF = 1e100L;

        if (dx == 0) {
            tMaxX = INF;
            tDeltaX = INF;
        } else {
            long long nextBX = (stepX > 0) ? (ax + 5) : (ax - 5);
            tMaxX = ((long double)(nextBX - ax)) / (long double)dx;
            tDeltaX = (long double)10 / fabsl((long double)dx);
        }

        if (dy == 0) {
            tMaxY = INF;
            tDeltaY = INF;
        } else {
            long long nextBY = (stepY > 0) ? (ay + 5) : (ay - 5);
            tMaxY = ((long double)(nextBY - ay)) / (long double)dy;
            tDeltaY = (long double)10 / fabsl((long double)dy);
        }

        int ans = 0;

        auto try_cell = [&](int x, int y) {
            if (x < 1 || x > 500 || y < 1 || y > 500) return;
            if (stamp[x][y] == qi) return;
            stamp[x][y] = qi;
            int id = idx_at[x][y];
            if (id < 0) return;
            long long ccx = (long long)x * 10;
            long long ccy = (long long)y * 10;
            if (seg_intersects_circle_scaled(ax, ay, bx, by, ccx, ccy, r10[id])) ans++;
        };

        auto process_cell = [&](int x, int y) {
            for (int ox = -1; ox <= 1; ++ox) {
                for (int oy = -1; oy <= 1; ++oy) {
                    try_cell(x + ox, y + oy);
                }
            }
        };

        process_cell(gx, gy);

        const long double EPS = 1e-18L;

        while (gx != gx_end || gy != gy_end) {
            if (fabsl(tMaxX - tMaxY) <= EPS) {
                gx += stepX;
                gy += stepY;
                tMaxX += tDeltaX;
                tMaxY += tDeltaY;
                process_cell(gx, gy);
            } else if (tMaxX < tMaxY) {
                gx += stepX;
                tMaxX += tDeltaX;
                process_cell(gx, gy);
            } else {
                gy += stepY;
                tMaxY += tDeltaY;
                process_cell(gx, gy);
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
