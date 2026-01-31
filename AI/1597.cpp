#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const double EPS = 1e-9;

struct PtI {
    ll x;
    ll y;
};

struct PtD {
    double x;
    double y;
};

ll crs(const PtI &a, const PtI &b, const PtI &c) {
    ll x1 = b.x - a.x;
    ll y1 = b.y - a.y;
    ll x2 = c.x - a.x;
    ll y2 = c.y - a.y;
    return x1 * y2 - y1 * x2;
}

bool in_tri(const PtI &a, const PtI &b, const PtI &c, const PtI &p) {
    ll c1 = crs(a, b, p);
    ll c2 = crs(b, c, p);
    ll c3 = crs(c, a, p);
    return c1 <= 0 && c2 <= 0 && c3 <= 0;
}

vector<array<PtI, 3>> tri_poly(const vector<PtI> &p) {
    int n = (int)p.size();
    vector<int> idx(n);
    for (int i = 0; i < n; i++) idx[i] = i;

    vector<array<PtI, 3>> ts;
    ts.reserve(max(0, n - 2));

    while ((int)idx.size() > 3) {
        bool fd = false;
        int m = (int)idx.size();

        for (int i = 0; i < m; i++) {
            int ip = idx[(i - 1 + m) % m];
            int ic = idx[i];
            int in = idx[(i + 1) % m];

            const PtI &a = p[ip];
            const PtI &b = p[ic];
            const PtI &c = p[in];

            if (crs(a, b, c) >= 0) continue;

            bool ok = true;
            for (int j = 0; j < m; j++) {
                if (j == (i - 1 + m) % m || j == i || j == (i + 1) % m) continue;
                const PtI &q = p[idx[j]];
                if (in_tri(a, b, c, q)) {
                    ok = false;
                    break;
                }
            }

            if (!ok) continue;

            ts.push_back({ a, b, c });
            idx.erase(idx.begin() + i);
            fd = true;
            break;
        }

        if (!fd) {
            break;
        }
    }

    if ((int)idx.size() == 3) {
        ts.push_back({ p[idx[0]], p[idx[1]], p[idx[2]] });
    }

    return ts;
}

vector<PtD> clip_x_ge(const vector<PtD> &pl, double x0) {
    vector<PtD> out;
    int n = (int)pl.size();
    if (n == 0) return out;

    for (int i = 0; i < n; i++) {
        PtD a = pl[i];
        PtD b = pl[(i + 1) % n];

        bool ina = a.x >= x0 - EPS;
        bool inb = b.x >= x0 - EPS;

        if (ina && inb) {
            out.push_back(b);
        } else if (ina && !inb) {
            double t = (x0 - a.x) / (b.x - a.x);
            PtD q = { x0, a.y + (b.y - a.y) * t };
            out.push_back(q);
        } else if (!ina && inb) {
            double t = (x0 - a.x) / (b.x - a.x);
            PtD q = { x0, a.y + (b.y - a.y) * t };
            out.push_back(q);
            out.push_back(b);
        }
    }

    return out;
}

vector<PtD> clip_x_le(const vector<PtD> &pl, double x1) {
    vector<PtD> out;
    int n = (int)pl.size();
    if (n == 0) return out;

    for (int i = 0; i < n; i++) {
        PtD a = pl[i];
        PtD b = pl[(i + 1) % n];

        bool ina = a.x <= x1 + EPS;
        bool inb = b.x <= x1 + EPS;

        if (ina && inb) {
            out.push_back(b);
        } else if (ina && !inb) {
            double t = (x1 - a.x) / (b.x - a.x);
            PtD q = { x1, a.y + (b.y - a.y) * t };
            out.push_back(q);
        } else if (!ina && inb) {
            double t = (x1 - a.x) / (b.x - a.x);
            PtD q = { x1, a.y + (b.y - a.y) * t };
            out.push_back(q);
            out.push_back(b);
        }
    }

    return out;
}

vector<PtD> clip_y_ge(const vector<PtD> &pl, double y0) {
    vector<PtD> out;
    int n = (int)pl.size();
    if (n == 0) return out;

    for (int i = 0; i < n; i++) {
        PtD a = pl[i];
        PtD b = pl[(i + 1) % n];

        bool ina = a.y >= y0 - EPS;
        bool inb = b.y >= y0 - EPS;

        if (ina && inb) {
            out.push_back(b);
        } else if (ina && !inb) {
            double t = (y0 - a.y) / (b.y - a.y);
            PtD q = { a.x + (b.x - a.x) * t, y0 };
            out.push_back(q);
        } else if (!ina && inb) {
            double t = (y0 - a.y) / (b.y - a.y);
            PtD q = { a.x + (b.x - a.x) * t, y0 };
            out.push_back(q);
            out.push_back(b);
        }
    }

    return out;
}

vector<PtD> clip_y_le(const vector<PtD> &pl, double y1) {
    vector<PtD> out;
    int n = (int)pl.size();
    if (n == 0) return out;

    for (int i = 0; i < n; i++) {
        PtD a = pl[i];
        PtD b = pl[(i + 1) % n];

        bool ina = a.y <= y1 + EPS;
        bool inb = b.y <= y1 + EPS;

        if (ina && inb) {
            out.push_back(b);
        } else if (ina && !inb) {
            double t = (y1 - a.y) / (b.y - a.y);
            PtD q = { a.x + (b.x - a.x) * t, y1 };
            out.push_back(q);
        } else if (!ina && inb) {
            double t = (y1 - a.y) / (b.y - a.y);
            PtD q = { a.x + (b.x - a.x) * t, y1 };
            out.push_back(q);
            out.push_back(b);
        }
    }

    return out;
}

double area_poly(const vector<PtD> &pl) {
    int n = (int)pl.size();
    if (n < 3) return 0.0;

    double s = 0.0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        s += pl[i].x * pl[j].y - pl[j].x * pl[i].y;
    }

    return fabs(s) * 0.5;
}

double tri_sq_area(const array<PtI, 3> &t, int x, int y) {
    ll mnx = min({ t[0].x, t[1].x, t[2].x });
    ll mxx = max({ t[0].x, t[1].x, t[2].x });
    ll mny = min({ t[0].y, t[1].y, t[2].y });
    ll mxy = max({ t[0].y, t[1].y, t[2].y });

    if (mxx <= x || mnx >= x + 1) return 0.0;
    if (mxy <= y || mny >= y + 1) return 0.0;

    vector<PtD> pl(3);
    for (int i = 0; i < 3; i++) pl[i] = { (double)t[i].x, (double)t[i].y };

    pl = clip_x_ge(pl, (double)x);
    pl = clip_x_le(pl, (double)(x + 1));
    pl = clip_y_ge(pl, (double)y);
    pl = clip_y_le(pl, (double)(y + 1));

    return area_poly(pl);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, w, h;
    cin >> n >> w >> h;

    vector<PtI> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y;
    }

    auto ts = tri_poly(p);

    vector<string> out(h, string(w, '.'));

    for (int yy = 0; yy < h; yy++) {
        for (int xx = 0; xx < w; xx++) {
            double a = 0.0;
            for (auto &t : ts) {
                a += tri_sq_area(t, xx, yy);
            }

            if (a < 0.25 - EPS) out[h - 1 - yy][xx] = '.';
            else if (a < 0.50 - EPS) out[h - 1 - yy][xx] = '+';
            else if (a < 0.75 - EPS) out[h - 1 - yy][xx] = 'o';
            else if (a < 1.00 - EPS) out[h - 1 - yy][xx] = '$';
            else out[h - 1 - yy][xx] = '#';
        }
    }

    for (int i = 0; i < h; i++) {
        cout << out[i] << "\n";
    }

    return 0;
}
