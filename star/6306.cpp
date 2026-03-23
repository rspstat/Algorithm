#include <bits/stdc++.h>
using namespace std;

using ld = long double;

static const ld EPS_T = 1e-9L;
static const ld EPS_D = 1e-14L;

struct Sphere {
    ld x, y, r;
};

struct Vec {
    ld x, y;
    Vec() : x(0), y(0) {}
    Vec(ld _x, ld _y) : x(_x), y(_y) {}
    Vec operator + (const Vec& o) const { return Vec(x + o.x, y + o.y); }
    Vec operator - (const Vec& o) const { return Vec(x - o.x, y - o.y); }
    Vec operator * (ld k) const { return Vec(x * k, y * k); }
};

static inline ld dot(const Vec& a, const Vec& b) { return a.x * b.x + a.y * b.y; }
static inline ld norm2(const Vec& a) { return dot(a, a); }
static inline ld norm(const Vec& a) { return sqrtl(norm2(a)); }

static inline Vec normalize(const Vec& v) {
    ld l = norm(v);
    return Vec(v.x / l, v.y / l);
}

static inline Vec reflect_dir(const Vec& d_unit, const Vec& n_unit) {
    ld k = 2.0L * dot(d_unit, n_unit);
    return Vec(d_unit.x - k * n_unit.x, d_unit.y - k * n_unit.y);
}

static bool ray_sphere_intersect(const Vec& P, const Vec& Dunit, const Sphere& s, ld& tHit) {
    Vec C(s.x, s.y);
    Vec m = P - C;

    ld b = dot(m, Dunit);
    ld c = dot(m, m) - s.r * s.r;

    ld disc = b * b - c;
    if (disc < 0) return false;

    ld sd = sqrtl(max<ld>(0.0L, disc));
    ld t1 = -b - sd;
    ld t2 = -b + sd;

    if (t1 > EPS_T) { tHit = t1; return true; }
    if (t2 > EPS_T) { tHit = t2; return true; }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int scene = 1;

    while (cin >> n) {
        if (n == 0) break;

        vector<Sphere> sp(n);
        for (int i = 0; i < n; i++) {
            long long xi, yi, ri;
            cin >> xi >> yi >> ri;
            sp[i] = {(ld)xi, (ld)yi, (ld)ri};
        }

        long long x, y, dx, dy;
        cin >> x >> y >> dx >> dy;

        Vec P((ld)x, (ld)y);
        Vec D = normalize(Vec((ld)dx, (ld)dy));

        vector<int> hitList;
        hitList.reserve(11);

        for (int step = 0; step < 11; step++) {
            int best = -1;
            ld bestT = 1e200L;

            for (int i = 0; i < n; i++) {
                ld t;
                if (ray_sphere_intersect(P, D, sp[i], t)) {
                    if (t < bestT) {
                        bestT = t;
                        best = i;
                    }
                }
            }

            if (best == -1) break;

            hitList.push_back(best + 1);

            Vec hit = P + D * bestT;
            Vec C(sp[best].x, sp[best].y);
            Vec Nraw = hit - C;
            ld nl = norm(Nraw);
            if (nl < EPS_D) break;
            Vec N(Nraw.x / nl, Nraw.y / nl);

            Vec R = reflect_dir(D, N);
            ld rl = norm(R);
            if (rl < EPS_D) break;
            R = Vec(R.x / rl, R.y / rl);

            P = hit + N * (1e-10L) + R * (1e-10L);
            D = R;
        }

        cout << "Scene " << scene << "\n";

        if (hitList.empty()) {
            cout << "inf\n\n";
        } else if ((int)hitList.size() <= 10) {
            for (int i = 0; i < (int)hitList.size(); i++) {
                if (i) cout << " ";
                cout << hitList[i];
            }
            cout << " inf\n\n";
        } else {
            for (int i = 0; i < 10; i++) {
                if (i) cout << " ";
                cout << hitList[i];
            }
            cout << " ...\n\n";
        }

        scene++;
    }

    return 0;
}
