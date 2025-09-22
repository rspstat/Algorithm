#include <bits/stdc++.h>
using namespace std;

struct Point{ long long x,y; };
struct Segment{ Point p1,p2; };

int ccw(const Point& a, const Point& b, const Point& c){
    long long v = (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x);
    if(v>0) return 1;
    if(v<0) return -1;
    return 0;
}

bool overlap1D(long long a1, long long a2, long long b1, long long b2){
    if(a1>a2) swap(a1,a2);
    if(b1>b2) swap(b1,b2);
    return max(a1,b1) <= min(a2,b2);
}

bool intersect(const Segment& A, const Segment& B){
    const auto &a=A.p1, &b=A.p2, &c=B.p1, &d=B.p2;
    int ab1 = ccw(a,b,c), ab2 = ccw(a,b,d);
    int cd1 = ccw(c,d,a), cd2 = ccw(c,d,b);

    // 공선(둘 다 0)인 경우: x축, y축 구간이 모두 겹쳐야 함
    if(ab1*ab2==0 && cd1*cd2==0){
        return overlap1D(a.x,b.x,c.x,d.x) && overlap1D(a.y,b.y,c.y,d.y);
    }
    // 일반 교차
    return ab1*ab2 <= 0 && cd1*cd2 <= 0;
}

struct DSU{
    vector<int> p, sz;
    DSU(int n): p(n), sz(n,1){ iota(p.begin(), p.end(), 0); }
    int find(int x){ return p[x]==x?x:p[x]=find(p[x]); }
    bool unite(int a,int b){
        a=find(a); b=find(b);
        if(a==b) return false;
        if(sz[a]<sz[b]) swap(a,b);
        p[b]=a; sz[a]+=sz[b];
        return true;
    }
    int size(int x){ return sz[find(x)]; }
};

void solve(){
    int n; cin>>n;
    vector<Segment> seg(n);
    for(int i=0;i<n;i++){
        cin>>seg[i].p1.x>>seg[i].p1.y>>seg[i].p2.x>>seg[i].p2.y;
    }

    DSU dsu(n);
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(intersect(seg[i], seg[j])) dsu.unite(i,j);
        }
    }

    int groups=0, mx=0;
    vector<int> seen(n,0);
    for(int i=0;i<n;i++){
        int r=dsu.find(i);
        if(!seen[r]){
            seen[r]=1;
            groups++;
            mx=max(mx, dsu.size(r));
        }
    }
    cout<<groups<<'\n'<<mx<<'\n';
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
