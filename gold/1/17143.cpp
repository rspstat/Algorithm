#include <bits/stdc++.h>
using namespace std;

struct S{int r,c,s,d,z; bool a;}; // a: alive

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int R,C,M; 
    if(!(cin>>R>>C>>M)) return 0;
    vector<S> v(M);
    for(int i=0;i<M;i++){
        cin>>v[i].r>>v[i].c>>v[i].s>>v[i].d>>v[i].z;
        v[i].a=true;
    }
    vector<vector<int>> g(R+1, vector<int>(C+1,-1));
    for(int i=0;i<M;i++) if(v[i].a) g[v[i].r][v[i].c]=i;

    int dr[5]={0,-1,1,0,0}, dc[5]={0,0,0,1,-1};
    auto rev=[&](int &d){ if(d==1) d=2; else if(d==2) d=1; else if(d==3) d=4; else d=3; };

    long long ans=0;
    for(int x=1;x<=C;x++){
        // catch
        for(int y=1;y<=R;y++){
            int i=g[y][x];
            if(i!=-1 && v[i].a){
                ans+=v[i].z;
                v[i].a=false;
                g[y][x]=-1;
                break;
            }
        }
        // move
        vector<vector<int>> ng(R+1, vector<int>(C+1,-1));
        for(int i=0;i<M;i++){
            if(!v[i].a) continue;
            int r=v[i].r, c=v[i].c, s=v[i].s, d=v[i].d;
            int cyc = (d<=2 ? (R>1?2*(R-1):0) : (C>1?2*(C-1):0));
            int m = (cyc? s%cyc : 0);
            while(m--){
                int nr=r+dr[d], nc=c+dc[d];
                if(nr<1||nr>R||nc<1||nc>C){
                    rev(d);
                    nr=r+dr[d]; nc=c+dc[d];
                }
                r=nr; c=nc;
            }
            v[i].r=r; v[i].c=c; v[i].d=d;
            int &j = ng[r][c];
            if(j==-1) j=i;
            else{
                if(v[j].z < v[i].z){ v[j].a=false; j=i; }
                else v[i].a=false;
            }
        }
        g.swap(ng);
    }
    cout<<ans<<"\n";
    return 0;
}
