#include <bits/stdc++.h>
using namespace std;

static const long double INF = 1e100L;

struct State {
    long double d;
    int i;
    int s;
    bool operator<(State const& other) const {
        return d > other.d;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    int g, a, f;
    cin >> N >> M >> g >> a >> f;

    int Sy, Sx, Ex;
    cin >> Sy >> Sx >> Ex;

    // position -> best car speed at that position (cars are unique among themselves, but may coincide with Ex)
    vector<long long> bestAt(N + 1, 0);
    for (int i = 0; i < M; i++) {
        int Xp;
        long long Sp;
        cin >> Xp >> Sp;
        bestAt[Xp] = max(bestAt[Xp], Sp);
    }

    // Build nodes: all car positions that exist + destination position Ex
    vector<int> pos;
    pos.reserve(M + 1);
    for (int x = 0; x <= N; x++) {
        if (bestAt[x] > 0) pos.push_back(x);
    }
    pos.push_back(Ex);
    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());

    int K = (int)pos.size();
    int dest = (int)(lower_bound(pos.begin(), pos.end(), Ex) - pos.begin());

    vector<long long> carSpeed(K, 0);
    for (int i = 0; i < K; i++) carSpeed[i] = bestAt[pos[i]];

    // Speeds list: {f} U {car speeds}
    vector<long long> speeds;
    speeds.reserve(K + 1);
    speeds.push_back((long long)f);
    for (int i = 0; i < K; i++) {
        if (carSpeed[i] > 0) speeds.push_back(carSpeed[i]);
    }
    sort(speeds.begin(), speeds.end());
    speeds.erase(unique(speeds.begin(), speeds.end()), speeds.end());

    int SF = (int)(lower_bound(speeds.begin(), speeds.end(), (long long)f) - speeds.begin());
    int S = (int)speeds.size();

    auto idxOfSpeed = [&](long long v) -> int {
        return (int)(lower_bound(speeds.begin(), speeds.end(), v) - speeds.begin());
    };

    // groundTime[x] for x=0..N by Dijkstra on (node, speedIdx)
    vector<long double> groundTime(N + 1, INF);

    vector<vector<long double>> dist(K, vector<long double>(S, INF));
    priority_queue<State> pq;

    auto runDijkstra = [&](int startX) -> long double {
        // reset dist
        for (int i = 0; i < K; i++) {
            fill(dist[i].begin(), dist[i].end(), INF);
        }
        while (!pq.empty()) pq.pop();

        // initial: can walk from startX to any node with speed f
        for (int i = 0; i < K; i++) {
            long double d0 = fabsl((long double)startX - (long double)pos[i]) / (long double)f;
            dist[i][SF] = d0;
            pq.push({d0, i, SF});
        }

        long double bestDest = INF;

        while (!pq.empty()) {
            State cur = pq.top();
            pq.pop();

            long double dcur = cur.d;
            int i = cur.i;
            int s = cur.s;

            if (dcur != dist[i][s]) continue;
            if (dcur >= bestDest) continue;

            if (i == dest) {
                bestDest = dcur;
                continue;
            }

            long long v = speeds[s];

            // upgrade at this node if there's a car here
            if (carSpeed[i] > 0) {
                long long nv = max(v, carSpeed[i]);
                int ns = idxOfSpeed(nv);
                if (dist[i][ns] > dcur) {
                    dist[i][ns] = dcur;
                    pq.push({dcur, i, ns});
                }
            }

            // move to any node j with current speed v
            for (int j = 0; j < K; j++) {
                if (j == i) continue;
                long double nd = dcur + fabsl((long double)pos[i] - (long double)pos[j]) / (long double)v;
                if (dist[j][s] > nd) {
                    dist[j][s] = nd;
                    pq.push({nd, j, s});
                }
            }
        }

        return bestDest;
    };

    for (int x = 0; x <= N; x++) {
        groundTime[x] = runDijkstra(x);
    }

    // Now try all landing integer x in [0..N]
    long double ans = INF;

    for (int x = 0; x <= N; x++) {
        long double d = fabsl((long double)x - (long double)Sx);

        // y_min = d*g/(2a)
        long double y_min = d * (long double)g / (2.0L * (long double)a);

        if (y_min > (long double)Sy + 1e-15L) continue; // impossible to reach x

        long double land_time = ((long double)Sy + y_min) / (long double)g;

        long double total = land_time + groundTime[x];
        if (total < ans) ans = total;
    }

    cout << fixed << setprecision(10) << (double)ans << "\n";
    return 0;
}
