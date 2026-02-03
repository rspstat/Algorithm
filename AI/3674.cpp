#include <bits/stdc++.h>
using namespace std;

using ld = long double;
using cd = complex<ld>;

static inline ld cabsld(const cd& z) { return hypot((ld)z.real(), (ld)z.imag()); }

struct FractalSolver {
    int n, d;
    vector<cd> g;
    vector<ld> segLen;
    cd g0, gN, E;
    ld Elen, L1;
    vector<ld> Ldepth;

    cd solve(int depth, const cd& A, const cd& B, ld dist) {
        const ld EPS = 1e-13L;
        cd V = B - A;
        ld vlen = cabsld(V);
        if (vlen < EPS) return A;

        ld s = vlen / Elen;
        cd uE = E / Elen;
        cd uV = V / vlen;
        cd rot = uV / uE;
        cd comb = rot * s;

        auto tr = [&](int idx) -> cd {
            return A + comb * (g[idx] - g0);
        };

        if (depth == 1) {
            for (int i = 0; i < n - 1; i++) {
                ld l = segLen[i] * s;
                if (dist > l + EPS) {
                    dist -= l;
                } else {
                    cd P = tr(i);
                    cd Q = tr(i + 1);
                    ld t = (l < EPS) ? 0.0L : max<ld>(0.0L, min<ld>(1.0L, dist / l));
                    return P + (Q - P) * t;
                }
            }
            return tr(n - 1);
        } else {
            ld factor = (s / Elen) * Ldepth[depth - 1];
            for (int i = 0; i < n - 1; i++) {
                ld part = segLen[i] * factor;
                if (dist > part + EPS) {
                    dist -= part;
                } else {
                    cd P = tr(i);
                    cd Q = tr(i + 1);
                    return solve(depth - 1, P, Q, dist);
                }
            }
            return tr(n - 1);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int c;
    cin >> c;
    cout.setf(std::ios::fixed);
    cout << setprecision(12);

    while (c--) {
        int n;
        cin >> n;
        vector<cd> g(n);
        for (int i = 0; i < n; i++) {
            long long x, y;
            cin >> x >> y;
            g[i] = cd((ld)x, (ld)y);
        }
        int d;
        cin >> d;
        ld f;
        cin >> f;

        FractalSolver fs;
        fs.n = n;
        fs.d = d;
        fs.g = g;
        fs.g0 = g[0];
        fs.gN = g[n - 1];
        fs.E = fs.gN - fs.g0;
        fs.Elen = cabsld(fs.E);

        fs.segLen.assign(n - 1, 0);
        fs.L1 = 0;
        for (int i = 0; i < n - 1; i++) {
            fs.segLen[i] = cabsld(g[i + 1] - g[i]);
            fs.L1 += fs.segLen[i];
        }

        fs.Ldepth.assign(d + 1, 0);
        fs.Ldepth[1] = fs.L1;
        ld R = fs.L1 / fs.Elen;
        for (int k = 2; k <= d; k++) fs.Ldepth[k] = fs.Ldepth[k - 1] * R;

        ld total = fs.Ldepth[d];
        ld target = f * total;
        if (target < 0) target = 0;
        if (target > total) target = total;

        cd ans = fs.solve(d, fs.g0, fs.gN, target);

        ld x = ans.real(), y = ans.imag();
        if (fabsl(x) < 5e-16L) x = 0;
        if (fabsl(y) < 5e-16L) y = 0;

        cout << "(" << (double)x << "," << (double)y << ")\n";
    }
    return 0;
}
