#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

int S;
vector<vector<int>> adj;
vector<int> sz;
vector<int> centroids;

// 서브트리 크기 계산 (Centroid를 찾기 위함)
void get_sz(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p) {
            get_sz(v, u);
            sz[u] += sz[v];
        }
    }
}

// 트리의 중심(Centroid) 찾기
void find_centroids(int u, int p) {
    bool is_centroid = true;
    for (int v : adj[u]) {
        if (v != p) {
            find_centroids(v, u);
            // 자식 쪽 서브트리가 전체의 절반을 넘으면 중심이 아님
            if (sz[v] > S / 2) is_centroid = false;
        }
    }
    // 부모 쪽(전체 - 현재 서브트리)이 전체의 절반을 넘으면 중심이 아님
    if (S - sz[u] > S / 2) is_centroid = false;
    
    if (is_centroid) centroids.push_back(u);
}

// 트리를 문자열로 인코딩 (AHU 알고리즘 아이디어)
string encode(int u, int p) {
    vector<string> sub_strings;
    for (int v : adj[u]) {
        if (v != p) {
            sub_strings.push_back(encode(v, u));
        }
    }
    // 자식들의 문자열을 사전순 정렬하여 순서 무관하게 만듦
    sort(sub_strings.begin(), sub_strings.end());
    
    string res = "(";
    for (const string& s : sub_strings) {
        res += s;
    }
    res += ")";
    return res;
}

void solve() {
    int N;
    if (!(cin >> N)) return;

    set<string> distinct_trees;

    while (N--) {
        cin >> S;
        adj.assign(S, vector<int>());
        for (int i = 0; i < S - 1; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // 1. 트리 사이즈 및 중심 찾기 전처리
        sz.assign(S, 0);
        centroids.clear();
        
        // 임의의 루트(0번)에서 사이즈 계산
        get_sz(0, -1);
        // 중심 찾기
        find_centroids(0, -1);

        // 2. 중심을 루트로 하여 인코딩 수행
        string canonical_form = "";
        for (int c : centroids) {
            string current_encoding = encode(c, -1);
            // 중심이 2개일 경우 사전순으로 앞서는 것을 선택
            if (canonical_form == "" || current_encoding < canonical_form) {
                canonical_form = current_encoding;
            }
        }

        distinct_trees.insert(canonical_form);
    }

    cout << distinct_trees.size() << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
