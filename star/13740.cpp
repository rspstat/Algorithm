#include <bits/stdc++.h>
using namespace std;

struct Pt {
    long long x, y;
    int id;
};

static inline long long crossLL(const Pt& a, const Pt& b, const Pt& c) {
    // (b-a) x (c-a)
    long long x1 = b.x - a.x;
    long long y1 = b.y - a.y;
    long long x2 = c.x - a.x;
    long long y2 = c.y - a.y;
    __int128 cr = (__int128)x1 * y2 - (__int128)y1 * x2;
    if (cr > 0) return 1;
    if (cr < 0) return -1;
    return 0; // no three collinear in input, so this won't happen for distinct points
}

static inline long double scoreAngle(const Pt& prev2, const Pt& prev1, const Pt& cand) {
    // angle between vector (prev1->prev2) and (prev1->cand)
    long double ux = (long double)(prev2.x - prev1.x);
    long double uy = (long double)(prev2.y - prev1.y);
    long double vx = (long double)(cand.x - prev1.x);
    long double vy = (long double)(cand.y - prev1.y);
    long double dot = ux * vx + uy * vy;
    long double lenv = sqrtl(vx * vx + vy * vy);
    // |u| is constant within this step, so comparing dot/|v| is enough
    return dot / lenv;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<Pt> p(N);
    for (int i = 0; i < N; i++) {
        cin >> p[i].x >> p[i].y;
        p[i].id = i + 1;
    }
    string s;
    cin >> s; // length N-2

    // 1) start = lowest y, then lowest x
    int st = 0;
    for (int i = 1; i < N; i++) {
        if (p[i].y < p[st].y || (p[i].y == p[st].y && p[i].x < p[st].x)) st = i;
    }

    vector<int> ans;
    vector<bool> used(N, false);
    ans.reserve(N);

    ans.push_back(p[st].id);
    used[st] = true;

    // 2) pick second point: closest direction to left (if s[0]=='R') else right
    long double ref = (s[0] == 'R') ? acosl(-1.0L) : 0.0L; // pi or 0
    int second = -1;
    long double bestDiff = 1e100L;

    for (int i = 0; i < N; i++) {
        if (used[i]) continue;
        long double ang = atan2l((long double)(p[i].y - p[st].y), (long double)(p[i].x - p[st].x)); // [-pi,pi]
        long double diff = ang - ref;
        // wrap to [-pi,pi]
        diff = atan2l(sinl(diff), cosl(diff));
        diff = fabsl(diff);

        if (diff < bestDiff) {
            bestDiff = diff;
            second = i;
        }
    }

    ans.push_back(p[second].id);
    used[second] = true;

    int prev2i = st;
    int prev1i = second;

    // 3) choose remaining points using pairs s[i], s[i+1]
    // we will pick N-3 points here, then append the last unused point.
    for (int i = 0; i < (int)s.size() - 1; i++) {
        char cur = s[i];
        char nxt = s[i + 1];
        bool wantMaxAngle = (cur == nxt); // same => farthest angle, different => nearest angle :contentReference[oaicite:1]{index=1}

        int pick = -1;

        // initialize bestScore depending on min/max
        // score is dot/|v| : larger => smaller angle, smaller => larger angle.
        long double bestScore = wantMaxAngle ? 1e100L : -1e100L;

        for (int j = 0; j < N; j++) {
            if (used[j]) continue;

            int side = crossLL(p[prev2i], p[prev1i], p[j]);
            if (cur == 'L') {
                if (side <= 0) continue;
            } else { // 'R'
                if (side >= 0) continue;
            }

            long double sc = scoreAngle(p[prev2i], p[prev1i], p[j]);

            if (!wantMaxAngle) {
                // want min angle => maximize score
                if (sc > bestScore) {
                    bestScore = sc;
                    pick = j;
                }
            } else {
                // want max angle => minimize score
                if (sc < bestScore) {
                    bestScore = sc;
                    pick = j;
                }
            }
        }

        // problem guarantees solution; pick should exist
        used[pick] = true;
        ans.push_back(p[pick].id);
        prev2i = prev1i;
        prev1i = pick;
    }

    // 4) append the last unused point
    for (int i = 0; i < N; i++) {
        if (!used[i]) {
            ans.push_back(p[i].id);
            break;
        }
    }

    for (int i = 0; i < N; i++) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}
