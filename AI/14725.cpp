#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

struct Node {
    map<string, Node*> ch;
};

Node* root = new Node();

void ins(vector<string>& v) {
    Node* cur = root;
    for (string& s : v) {
        if (cur->ch.find(s) == cur->ch.end()) {
            cur->ch[s] = new Node();
        }
        cur = cur->ch[s];
    }
}

void dfs(Node* cur, int d) {
    // map은 자동 정렬되므로 순서대로 방문
    for (auto& it : cur->ch) {
        for (int i = 0; i < d; i++) cout << "--";
        cout << it.first << '\n';
        dfs(it.second, d + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    while (n--) {
        int k;
        cin >> k;
        vector<string> v(k);
        for (int i = 0; i < k; i++) cin >> v[i];
        ins(v);
    }

    dfs(root, 0);

    return 0;
}
