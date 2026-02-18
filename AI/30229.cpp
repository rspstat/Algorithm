#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long b1i, b2i, hi_i;
    cin >> b1i >> b2i >> hi_i;

    double b1 = (double)b1i;
    double b2 = (double)b2i;
    double h  = (double)hi_i;

    auto feasible = [&](double T) -> bool {
        double denom = b1 + b2;
        double yl = (b2 * h - T) / denom;
        double yu = (b2 * h + T) / denom;
        yl = max(yl, 0.0);
        yu = min(yu, h);
        if (yl > yu) return false;

        auto g = [&](double y) -> double {
            double hb1 = h * b1;
            double bb = b1 - b2;

            double L0 = 0.0;
            double L1 = b1 * y - T;
            double L2 = b2 * h - b2 * y - T;
            double L3 = (hb1 - bb * y - T) * 0.5;
            double L4 = hb1 - (2.0 * b1 - b2) * y - T;
            double L5 = (hb1 - b2 * h) - (b1 - 2.0 * b2) * y - T;

            double U0 = hb1 - bb * y;
            double U1 = b1 * y + T;
            double U2 = b2 * h - b2 * y + T;
            double U3 = (hb1 - bb * y + T) * 0.5;
            double U4 = hb1 - (2.0 * b1 - b2) * y + T;
            double U5 = (hb1 - b2 * h) - (b1 - 2.0 * b2) * y + T;

            double LB = max({L0, L1, L2, L3, L4, L5});
            double UB = min({U0, U1, U2, U3, U4, U5});
            return LB - UB;
        };

        double l = yl, r = yu;
        for (int it = 0; it < 200; ++it) {
            double m1 = (2.0 * l + r) / 3.0;
            double m2 = (l + 2.0 * r) / 3.0;
            if (g(m1) < g(m2)) r = m2;
            else l = m1;
        }

        double ymid = (l + r) * 0.5;
        return g(ymid) <= 1e-12;
    };

    double lo = 0.0;
    double hi = (b1 + b2) * h; // doubled total area is an absolute upper bound on doubled range
    for (int it = 0; it < 80; ++it) {
        double mid = (lo + hi) * 0.5;
        if (feasible(mid)) hi = mid;
        else lo = mid;
    }

    double ans = hi * 0.5; // convert doubled range back to area
    cout.setf(std::ios::fixed);
    cout << setprecision(9) << ans << "\n";
    return 0;
}
