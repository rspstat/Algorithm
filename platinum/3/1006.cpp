#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
int N, W;
vector<int> up, dn;

int calc(bool topWrap, bool botWrap) {
    vector<int> a(N, INF), b(N, INF), c(N + 1, INF);
    
    if (topWrap && botWrap) {
        a[1] = b[1] = 1; 
        c[1] = 0;
    }
    else if (topWrap) {
        a[1] = 2; 
        b[1] = (dn[0] + dn[1] <= W) ? 1 : 2; 
        c[1] = 1;
    }
    else if (botWrap) {
        a[1] = (up[0] + up[1] <= W) ? 1 : 2; 
        b[1] = 2; 
        c[1] = 1;
    }
    else {
        a[0] = b[0] = 1; 
        c[0] = 0;
    }
    
    auto upd = [&](int s) {
        for (int i = s; i < N; i++) {
            c[i + 1] = min({c[i + 1], a[i] + 1, b[i] + 1});
            
            if (up[i] + dn[i] <= W) 
                c[i + 1] = min(c[i + 1], c[i] + 1);
            
            if (i && up[i - 1] + up[i] <= W && dn[i - 1] + dn[i] <= W) 
                c[i + 1] = min(c[i + 1], c[i - 1] + 2);
            
            if (i < N - 1) {
                a[i + 1] = min(a[i + 1], c[i + 1] + 1);
                b[i + 1] = min(b[i + 1], c[i + 1] + 1);
                
                if (up[i] + up[i + 1] <= W) 
                    a[i + 1] = min(a[i + 1], b[i] + 1);
                
                if (dn[i] + dn[i + 1] <= W) 
                    b[i + 1] = min(b[i + 1], a[i] + 1);
            }
        }
    };
    
    upd((topWrap || botWrap) ? 1 : 0);
    
    if (topWrap && botWrap) 
        return c[N - 1] + 2;
    if (topWrap) 
        return b[N - 1] + 1;
    if (botWrap) 
        return a[N - 1] + 1;
    return c[N];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        cin >> N >> W;
        up.assign(N, 0); 
        dn.assign(N, 0);
        
        for (int i = 0; i < N; i++) 
            cin >> up[i];
        for (int i = 0; i < N; i++) 
            cin >> dn[i];
        
        if (N == 1) {
            cout << (up[0] + dn[0] <= W ? 1 : 2) << "\n"; 
            continue;
        }
        
        int ans = calc(0, 0);
        
        if (up[0] + up[N - 1] <= W) 
            ans = min(ans, calc(1, 0));
        
        if (dn[0] + dn[N - 1] <= W) 
            ans = min(ans, calc(0, 1));
        
        if (up[0] + up[N - 1] <= W && dn[0] + dn[N - 1] <= W) 
            ans = min(ans, calc(1, 1));
        
        cout << ans << "\n";
    }
    
    return 0;
}
