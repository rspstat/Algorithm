#include <bits/stdc++.h>
using namespace std;

using ld = long double;

static const ld G = 9.8L;
static const ld EPS = 1e-12L;

struct Rect {
    ld L, B, R, T;
};

static inline void add_root_interval(vector<ld>& cuts, ld x) {
    if (isfinite((double)x)) cuts.push_back(x);
}

static inline bool solve_quad(ld A, ld B, ld C, ld& r1, ld& r2) {
    if (fabsl(A) < EPS) {
        if (fabsl(B) < EPS) return false;
        r1 = r2 = -C / B;
        return true;
    }
    ld D = B * B - 4 * A * C;
    if (D < -1e-14L) return false;
    if (D < 0) D = 0;
    ld s = sqrtl(D);
    ld q = -0.5L * (B + (B >= 0 ? s : -s));
    ld x1 = q / A;
    ld x2 = (fabsl(q) < EPS ? x1 : C / q);
    r1 = min(x1, x2);
    r2 = max(x1, x2);
    return true;
}

static inline ld y_on_traj(ld a, ld k, ld x) {
    return a * x - k * (1 + a * a) * x * x;
}

static inline bool traj_hits_rect(ld a, ld k, ld Xlim, const Rect& rc) {
    ld l = max<ld>(0.0L, rc.L);
    ld r = min<ld>(Xlim, rc.R);
    if (l > r + EPS) return false;

    ld yl = y_on_traj(a, k, l);
    ld yr = y_on_traj(a, k, r);

    ld ymin = min(yl, yr);
    ld ymax = max(yl, yr);

    ld denom = 2 * k * (1 + a * a);
    if (denom > EPS) {
        ld xv = a / denom;
        if (xv >= l - EPS && xv <= r + EPS) {
            ld yv = y_on_traj(a, k, xv);
            ymax = max(ymax, yv);
            ymin = min(ymin, min(yl, yr));
        }
    }

    if (ymax >= rc.B - 1e-12L && ymin <= rc.T + 1e-12L) return true;
    return false;
}

static inline bool egg_hits_rect(ld X, ld Y, ld ydrop, const Rect& rc) {
    if (X < rc.L - 1e-12L || X > rc.R + 1e-12L) return false;
    ld lo = max(Y, rc.B);
    ld hi = min(ydrop, rc.T);
    return lo <= hi + 1e-12L;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    int Vint, Xint, Yint;
    if (!(cin >> N >> Vint >> Xint >> Yint)) return 0;

    ld V = (ld)Vint;
    ld X = (ld)Xint;
    ld Y = (ld)Yint;

    vector<Rect> obs(N);
    for (int i = 0; i < N; i++) {
        ld L, B, R, T;
        cin >> L >> B >> R >> T;
        if (L > R) swap(L, R);
        if (B > T) swap(B, T);
        obs[i] = {L, B, R, T};
    }

    if (V <= 0) {
        cout << "No\n";
        return 0;
    }

    ld k = G / (2 * V * V);

    ld A = -k * X * X;
    ld B = X;
    ld C = -k * X * X - Y;

    ld aL, aR;
    if (!solve_quad(A, B, C, aL, aR)) {
        cout << "No\n";
        return 0;
    }

    vector<ld> cuts;
    cuts.reserve(2000);
    cuts.push_back(aL);
    cuts.push_back(aR);

    auto add_roots_y_eq = [&](ld x0, ld y0) {
        if (x0 <= EPS) return;
        ld AA = -k * x0 * x0;
        ld BB = x0;
        ld CC = -k * x0 * x0 - y0;
        ld r1, r2;
        if (solve_quad(AA, BB, CC, r1, r2)) {
            add_root_interval(cuts, r1);
            add_root_interval(cuts, r2);
        }
    };

    auto add_roots_vertex_x = [&](ld x0) {
        if (x0 <= EPS) return;
        ld AA = 2 * k * x0;
        ld BB = -1;
        ld CC = 2 * k * x0;
        ld r1, r2;
        if (solve_quad(AA, BB, CC, r1, r2)) {
            add_root_interval(cuts, r1);
            add_root_interval(cuts, r2);
        }
    };

    auto add_roots_vertex_y = [&](ld H) {
        ld denom = 1 - 4 * k * H;
        if (denom <= 1e-14L) return;
        ld val = (4 * k * H) / denom;
        if (val < -1e-14L) return;
        if (val < 0) val = 0;
        ld r = sqrtl(val);
        add_root_interval(cuts, r);
        add_root_interval(cuts, -r);
    };

    for (int i = 0; i < N; i++) {
        ld l = max<ld>(0.0L, obs[i].L);
        ld r = min<ld>(X, obs[i].R);
        if (l <= r + EPS) {
            add_roots_y_eq(l, obs[i].B);
            add_roots_y_eq(l, obs[i].T);
            add_roots_y_eq(r, obs[i].B);
            add_roots_y_eq(r, obs[i].T);
            add_roots_vertex_x(l);
            add_roots_vertex_x(r);
            add_roots_vertex_y(obs[i].B);
            add_roots_vertex_y(obs[i].T);
        }
        if (X >= obs[i].L - EPS && X <= obs[i].R + EPS) {
            add_roots_y_eq(X, obs[i].B);
            add_roots_y_eq(X, obs[i].T);
        }
    }

    sort(cuts.begin(), cuts.end());
    vector<ld> uniq;
    uniq.reserve(cuts.size());
    for (ld v : cuts) {
        if (v < aL - 1e-10L || v > aR + 1e-10L) continue;
        if (uniq.empty() || fabsl(v - uniq.back()) > 1e-10L) uniq.push_back(v);
    }

    if (uniq.empty()) {
        cout << "No\n";
        return 0;
    }

    auto feasible = [&](ld a) -> bool {
        ld ydrop = y_on_traj(a, k, X);
        if (ydrop < Y - 1e-10L) return false;

        for (int i = 0; i < N; i++) {
            if (traj_hits_rect(a, k, X, obs[i])) return false;
        }
        for (int i = 0; i < N; i++) {
            if (egg_hits_rect(X, Y, ydrop, obs[i])) return false;
        }
        return true;
    };

    bool ok = false;

    if (uniq.size() == 1) {
        ok = feasible(uniq[0]);
    } else {
        for (size_t i = 0; i + 1 < uniq.size(); i++) {
            ld Lc = uniq[i], Rc = uniq[i + 1];
            if (Rc - Lc < 1e-12L) continue;
            ld mid = (Lc + Rc) / 2;
            if (mid < aL) mid = (aL + Rc) / 2;
            if (mid > aR) mid = (Lc + aR) / 2;
            if (feasible(mid)) {
                ok = true;
                break;
            }
        }
        if (!ok) {
            if (feasible((uniq.front() + min(uniq.front() + 1e-7L, aR)) / 2)) ok = true;
            if (!ok && feasible((max(uniq.back() - 1e-7L, aL) + uniq.back()) / 2)) ok = true;
        }
    }

    cout << (ok ? "Yes\n" : "No\n");
    return 0;
}
