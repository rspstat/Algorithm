#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct P2 {
    ll x, y;
    P2() : x(0), y(0) {}
    P2(ll _x, ll _y) : x(_x), y(_y) {}
    P2 operator + (const P2& o) const { return P2(x + o.x, y + o.y); }
    P2 operator - (const P2& o) const { return P2(x - o.x, y - o.y); }
    P2 operator * (ll k) const { return P2(x * k, y * k); }
};

struct P3 {
    ll x, y, z;
};

static inline ll sq(ll a) { return a * a; }
static inline ll cross2(const P2& a, const P2& b) { return a.x * b.y - a.y * b.x; }
static inline int sgn(ll v) { return (v > 0) - (v < 0); }

struct Face {
    array<int,4> v;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll lx, ly, lz, x, y, z;
    while (cin >> lx >> ly >> lz >> x >> y >> z) {
        if (lx == 0 && ly == 0 && lz == 0 && x == 0 && y == 0 && z == 0) break;

        vector<P3> V(8);
        V[0] = {0,0,0};
        V[1] = {lx,0,0};
        V[2] = {lx,ly,0};
        V[3] = {0,ly,0};
        V[4] = {0,0,lz};
        V[5] = {lx,0,lz};
        V[6] = {lx,ly,lz};
        V[7] = {0,ly,lz};

        const int Z0 = 0, Z1 = 1, Y0 = 2, Y1 = 3, X0 = 4, X1 = 5;
        vector<Face> F(6);
        F[Z0].v = {0,1,2,3};
        F[Z1].v = {4,5,6,7};
        F[Y0].v = {0,1,5,4};
        F[Y1].v = {3,2,6,7};
        F[X0].v = {0,3,7,4};
        F[X1].v = {1,2,6,5};

        map<pair<int,int>, pair<int,int>> edgeOwner;
        vector<vector<pair<int,int>>> adj(6);
        adj.assign(6, {});
        vector<array<int,4>> neigh(6);
        for (int i = 0; i < 6; i++) neigh[i].fill(-1);

        for (int fi = 0; fi < 6; fi++) {
            for (int e = 0; e < 4; e++) {
                int a = F[fi].v[e];
                int b = F[fi].v[(e + 1) % 4];
                pair<int,int> key = {min(a,b), max(a,b)};
                auto it = edgeOwner.find(key);
                if (it == edgeOwner.end()) {
                    edgeOwner[key] = {fi, e};
                } else {
                    int fj = it->second.first;
                    int ej = it->second.second;
                    neigh[fi][e] = fj;
                    neigh[fj][ej] = fi;
                }
            }
        }

        vector<int> startFaces = {Z0, Y0, X0};
        vector<int> targetFaces;
        if (x == 0) targetFaces.push_back(X0);
        if (x == lx) targetFaces.push_back(X1);
        if (y == 0) targetFaces.push_back(Y0);
        if (y == ly) targetFaces.push_back(Y1);
        if (z == 0) targetFaces.push_back(Z0);
        if (z == lz) targetFaces.push_back(Z1);
        sort(targetFaces.begin(), targetFaces.end());
        targetFaces.erase(unique(targetFaces.begin(), targetFaces.end()), targetFaces.end());

        P3 T3 = {x,y,z};

        auto startPlacement = [&](int sf) -> array<P2,4> {
            array<P2,4> c;
            if (sf == Z0) {
                c[0] = {0,0}; c[1] = {lx,0}; c[2] = {lx,ly}; c[3] = {0,ly};
            } else if (sf == Y0) {
                c[0] = {0,0}; c[1] = {lx,0}; c[2] = {lx,lz}; c[3] = {0,lz};
            } else {
                c[0] = {0,0}; c[1] = {ly,0}; c[2] = {ly,lz}; c[3] = {0,lz};
            }
            return c;
        };

        auto dist3 = [&](int va, int vb) -> ll {
            ll dx = V[va].x - V[vb].x;
            ll dy = V[va].y - V[vb].y;
            ll dz = V[va].z - V[vb].z;
            return llround(sqrt((long double)(dx*dx + dy*dy + dz*dz)));
        };

        auto target2D = [&](const array<P2,4>& c2, int faceId) -> P2 {
            int v0 = F[faceId].v[0];
            int v1 = F[faceId].v[1];
            int v3 = F[faceId].v[3];

            P2 P0 = c2[0], P1 = c2[1], P3p = c2[3];

            auto addAlong = [&](P2 base, P2 edgeVec2, int coordIdx, ll delta3, ll edgeLen3) -> P2 {
                if (edgeVec2.x != 0) {
                    ll step = (edgeVec2.x > 0 ? 1 : -1);
                    ll s3 = (delta3 >= 0 ? 1 : -1);
                    ll d = llabs(delta3);
                    return base + P2(step * s3 * d, 0);
                } else {
                    ll step = (edgeVec2.y > 0 ? 1 : -1);
                    ll s3 = (delta3 >= 0 ? 1 : -1);
                    ll d = llabs(delta3);
                    return base + P2(0, step * s3 * d);
                }
            };

            P3 V0 = V[v0], V1 = V[v1], V3 = V[v3];

            ll dx1 = V1.x - V0.x, dy1 = V1.y - V0.y, dz1 = V1.z - V0.z;
            ll dx3 = V3.x - V0.x, dy3 = V3.y - V0.y, dz3 = V3.z - V0.z;

            P2 res = P0;

            if (dx1 != 0) res = addAlong(res, P1 - P0, 0, (T3.x - V0.x), llabs(dx1));
            else if (dy1 != 0) res = addAlong(res, P1 - P0, 1, (T3.y - V0.y), llabs(dy1));
            else res = addAlong(res, P1 - P0, 2, (T3.z - V0.z), llabs(dz1));

            if (dx3 != 0) res = addAlong(res, P3p - P0, 0, (T3.x - V0.x), llabs(dx3));
            else if (dy3 != 0) res = addAlong(res, P3p - P0, 1, (T3.y - V0.y), llabs(dy3));
            else res = addAlong(res, P3p - P0, 2, (T3.z - V0.z), llabs(dz3));

            return res;
        };

        ll best = (1LL<<62);

        vector<int> path;
        vector<int> vis(6, 0);

        auto computeForPath = [&](int sf, int tf, const vector<int>& pathFaces) {
            array<array<P2,4>, 6> placed;
            array<char, 6> has{};
            has.fill(0);

            placed[sf] = startPlacement(sf);
            has[sf] = 1;

            for (int pi = 0; pi + 1 < (int)pathFaces.size(); pi++) {
                int fcur = pathFaces[pi];
                int fnxt = pathFaces[pi + 1];

                int ecur = -1;
                for (int e = 0; e < 4; e++) if (neigh[fcur][e] == fnxt) { ecur = e; break; }
                if (ecur == -1) return;

                int va = F[fcur].v[ecur];
                int vb = F[fcur].v[(ecur + 1) % 4];

                int ia = -1, ib = -1;
                for (int k = 0; k < 4; k++) {
                    if (F[fnxt].v[k] == va) ia = k;
                    if (F[fnxt].v[k] == vb) ib = k;
                }
                if (ia == -1 || ib == -1) return;
                if (!((ia + 1) % 4 == ib || (ib + 1) % 4 == ia)) return;

                P2 Pa, Pb;
                int idxAcur = -1, idxBcur = -1;
                for (int k = 0; k < 4; k++) if (F[fcur].v[k] == va) idxAcur = k;
                for (int k = 0; k < 4; k++) if (F[fcur].v[k] == vb) idxBcur = k;
                if (idxAcur == -1 || idxBcur == -1) return;

                Pa = placed[fcur][idxAcur];
                Pb = placed[fcur][idxBcur];

                int nearA, nearB;
                if ((ia + 1) % 4 == ib) {
                    nearA = (ia + 3) % 4;
                    nearB = (ib + 1) % 4;
                } else {
                    nearA = (ia + 1) % 4;
                    nearB = (ib + 3) % 4;
                }

                ll width = dist3(F[fnxt].v[ia], F[fnxt].v[nearA]);

                P2 evec = Pb - Pa;
                P2 perp1;
                if (evec.y == 0) {
                    perp1 = P2(0, (evec.x > 0 ? width : -width));
                } else {
                    perp1 = P2((evec.y > 0 ? -width : width), 0);
                }
                P2 perp2 = P2(-perp1.x, -perp1.y);

                P2 sum = placed[fcur][0] + placed[fcur][1] + placed[fcur][2] + placed[fcur][3];
                ll side = cross2(evec, sum - Pa * 4);

                ll c1 = cross2(evec, perp1);
                P2 perp;
                if (side > 0) perp = (c1 < 0 ? perp1 : perp2);
                else perp = (c1 > 0 ? perp1 : perp2);

                array<P2,4> nxtC;
                nxtC.fill(P2(0,0));
                nxtC[ia] = Pa;
                nxtC[ib] = Pb;
                nxtC[nearA] = Pa + perp;
                nxtC[nearB] = Pb + perp;

                has[fnxt] = 1;
                placed[fnxt] = nxtC;
            }

            if (!has[tf]) return;
            P2 t2 = target2D(placed[tf], tf);
            best = min(best, sq(t2.x) + sq(t2.y));
        };

        function<void(int,int,int)> dfs = [&](int u, int tf, int sf) {
            if (u == tf) {
                computeForPath(sf, tf, path);
                return;
            }
            for (int e = 0; e < 4; e++) {
                int v = neigh[u][e];
                if (v == -1) continue;
                if (vis[v]) continue;
                vis[v] = 1;
                path.push_back(v);
                dfs(v, tf, sf);
                path.pop_back();
                vis[v] = 0;
            }
        };

        for (int sf : startFaces) {
            for (int tf : targetFaces) {
                path.clear();
                fill(vis.begin(), vis.end(), 0);
                vis[sf] = 1;
                path.push_back(sf);
                dfs(sf, tf, sf);
            }
        }

        cout << best << "\n";
    }
    return 0;
}
