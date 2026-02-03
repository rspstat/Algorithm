#include <bits/stdc++.h>
using namespace std;

using ld = long double;

struct Pt {
    ld x, y;
};

static inline ld evalHalf(ld a, ld b, ld c, const Pt& p) {
    return a * p.x + b * p.y - c;
}

static vector<Pt> clipPoly(const vector<Pt>& poly, ld a, ld b, ld c) {
    const ld EPS = 1e-12L;
    vector<Pt> out;
    int m = (int)poly.size();
    if (m == 0) return out;

    for (int i = 0; i < m; i++) {
        Pt S = poly[i];
        Pt E = poly[(i + 1) % m];
        ld vS = evalHalf(a, b, c, S);
        ld vE = evalHalf(a, b, c, E);
        bool inS = (vS <= EPS);
        bool inE = (vE <= EPS);

        if (inS && inE) {
            out.push_back(E);
        } else if (inS && !inE) {
            ld denom = (vE - vS);
            if (fabsl(denom) > EPS) {
                ld t = (-vS) / denom;
                Pt I{S.x + (E.x - S.x) * t, S.y + (E.y - S.y) * t};
                out.push_back(I);
            }
        } else if (!inS && inE) {
            ld denom = (vE - vS);
            if (fabsl(denom) > EPS) {
                ld t = (-vS) / denom;
                Pt I{S.x + (E.x - S.x) * t, S.y + (E.y - S.y) * t};
                out.push_back(I);
            }
            out.push_back(E);
        }
    }
    return out;
}

static ld areaPoly(const vector<Pt>& poly) {
    int m = (int)poly.size();
    if (m < 3) return 0;
    ld a = 0;
    for (int i = 0; i < m; i++) {
        int j = (i + 1) % m;
        a += poly[i].x * poly[j].y - poly[j].x * poly[i].y;
    }
    return fabsl(a) * 0.5L;
}

static void addCloserHalfplanes(vector<Pt>& poly, const Pt& Pi, const Pt& Pj) {
    ld a = 2 * (Pj.x - Pi.x);
    ld b = 2 * (Pj.y - Pi.y);
    ld c = (Pj.x * Pj.x + Pj.y * Pj.y) - (Pi.x * Pi.x + Pi.y * Pi.y);
    poly = clipPoly(poly, a, b, c);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout.setf(std::ios::fixed);
    cout << setprecision(5);

    int tc = 1;
    while (true) {
        long long x1, y1, x2, y2, x3, y3;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        if (!cin) return 0;
        if (x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0 && x3 == 0 && y3 == 0) break;

        Pt IC{(ld)x1, (ld)y1};
        Pt PC{(ld)x2, (ld)y2};
        Pt ACM{(ld)x3, (ld)y3};

        vector<Pt> poly = {
            {0.0L, 0.0L},
            {10000.0L, 0.0L},
            {10000.0L, 10000.0L},
            {0.0L, 10000.0L}
        };

        addCloserHalfplanes(poly, IC, PC);
        addCloserHalfplanes(poly, IC, ACM);

        ld a = areaPoly(poly);
        ld prob = a / (10000.0L * 10000.0L);

        cout << tc << " " << (double)prob << "\n";
        tc++;
    }
    return 0;
}
