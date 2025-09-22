#include <bits/stdc++.h>
using namespace std;
const int MAXN=10;
int N,bd[MAXN][MAXN];
vector<pair<int,int>> blk,wht; // cell lists
bool d1[20],d2[20]; // diag flags
int best; // cur max

// backtrack
void dfs(const vector<pair<int,int>>& v,int idx,int cnt){
    if(idx==v.size()){best=max(best,cnt);return;} // end
    auto [r,c]=v[idx];
    int a=r+c,b=r-c+N-1; // diag idx
    if(!d1[a]&&!d2[b]){ // place
        d1[a]=d2[b]=1;
        dfs(v,idx+1,cnt+1);
        d1[a]=d2[b]=0;
    }
    dfs(v,idx+1,cnt); // skip
}

// solve one color
int solve(const vector<pair<int,int>>& v){
    memset(d1,0,sizeof d1);
    memset(d2,0,sizeof d2);
    best=0;
    dfs(v,0,0);
    return best;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>N;
    for(int i=0;i<N;i++)for(int j=0;j<N;j++){
        cin>>bd[i][j];
        if(!bd[i][j])continue; // blocked
        ((i+j)&1?wht:blk).push_back({i,j});
    }
    cout<<solve(blk)+solve(wht)<<"\n";
    return 0;
}
