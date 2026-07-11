#include <bits/stdc++.h>
using namespace std;

const int MOD = 10007;

int add(int a, int b){ a+=b; if(a>=MOD) a-=MOD; return a; }
int subm(int a, int b){ a-=b; if(a<0) a+=MOD; return a; }
int mul(int a, int b){ return int((a*1LL*b)%MOD); }

int modpow(int a, int e){
    int r=1;
    while(e){
        if(e&1) r=mul(r,a);
        a=mul(a,a);
        e>>=1;
    }
    return r;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; 
    if(!(cin >> n)) return 0;
    if(n < 4){ cout << 0 << "\n"; return 0; }

    const int M = 52;
    vector<int> f(M+1,1), invf(M+1,1);
    for(int i=1;i<=M;i++) f[i]=mul(f[i-1], i);
    invf[M]=modpow(f[M], MOD-2);
    for(int i=M;i>0;i--) invf[i-1]=mul(invf[i], i);

    auto C = [&](int N, int K)->int{
        if(K<0||K>N) return 0;
        return mul(f[N], mul(invf[K], invf[N-K]));
    };

    int ans = 0;
    for(int m=1; m<=13 && 4*m<=n; ++m){
        int waysRanks = C(13, m);
        int waysRest  = C(52 - 4*m, n - 4*m);
        int term = mul(waysRanks, waysRest);
        if(m & 1) ans = add(ans, term);
        else      ans = subm(ans, term);
    }
    cout << ans << "\n";
    return 0;
}
