#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int parent_node[MAXN];
int p_idx[MAXN]; 
int D[MAXN];
long long total_moves = 0;
int last_node = 0;
int depth_last = 0;

void build_tree(int u, int p) {
    parent_node[u] = p;
    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if (v == p) {
            p_idx[u] = i;
        } else {
            build_tree(v, u);
        }
    }
}

void calc_required(int u) {
    int req = 1;
    if (u == 1) {
        for (int v : adj[u]) {
            calc_required(v);
            req = max(req, D[v]);
        }
    } else {
        int pi = p_idx[u];
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            if (v == parent_node[u]) continue;
            calc_required(v);
            if (i < pi) {
                req = max(req, D[v]);
            } else {
                req = max(req, D[v] + 1);
            }
        }
    }
    D[u] = req;
}

void solve_moves(int u, int assigned, bool on_path, int depth) {
    if (on_path) {
        last_node = u;
        depth_last = depth;
    }

    if (u != 1) {
        long long visits = assigned;
        if (on_path) {
            total_moves += (2 * visits - 1);
        } else {
            total_moves += (2 * visits);
        }
    }

    if (adj[u].empty() || (u != 1 && adj[u].size() == 1)) return;

    int target_child = -1;
    if (on_path) {
        if (u == 1) {
            for (int i = (int)adj[u].size() - 1; i >= 0; i--) {
                int v = adj[u][i];
                if (D[v] == assigned) {
                    target_child = v;
                    break;
                }
            }
        } else {
            int pi = p_idx[u];
            if (assigned == 1) {
                for (int i = pi - 1; i >= 0; i--) {
                    int v = adj[u][i];
                    if (v == parent_node[u]) continue;
                    if (D[v] == 1) {
                        target_child = v;
                        break;
                    }
                }
            } else {
                bool found = false;
                for (int i = pi - 1; i >= 0; i--) {
                    int v = adj[u][i];
                    if (v == parent_node[u]) continue;
                    if (D[v] == assigned) {
                        target_child = v;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    for (int i = (int)adj[u].size() - 1; i > pi; i--) {
                        int v = adj[u][i];
                        if (v == parent_node[u]) continue;
                        if (D[v] == assigned - 1) {
                            target_child = v;
                            break;
                        }
                    }
                }
            }
        }
    }

    if (u == 1) {
        bool past_target = false;
        for (int i = (int)adj[u].size() - 1; i >= 0; i--) {
            int v = adj[u][i];
            if (on_path && v == target_child) {
                solve_moves(v, assigned, true, depth + 1);
                past_target = true;
            } else {
                int pass = assigned;
                if (on_path && !past_target) pass--; 
                if (pass > 0) solve_moves(v, pass, false, depth + 1);
            }
        }
    } else {
        int pi = p_idx[u];
        
        auto process_child = [&](int v, int base_pass) {
             if (on_path && v == target_child) {
                 solve_moves(v, base_pass, true, depth + 1);
                 return true;
             } else {
                 int pass = base_pass;
                 if (on_path && target_child != -2) pass--; 
                 if (pass > 0) solve_moves(v, pass, false, depth + 1);
                 return false;
             }
        };

        bool target_processed = false;

        // Pre-children (0 ~ pi-1)
        for (int i = pi - 1; i >= 0; i--) {
            int v = adj[u][i];
            if (v == parent_node[u]) continue;
            
            int base = assigned;
            if (target_processed) {
                 if (base > 0) solve_moves(v, base, false, depth + 1);
            } else {
                if (process_child(v, base)) {
                    target_processed = true;
                    target_child = -2; 
                }
            }
        }

        // Post-children (adj.size()-1 ~ pi+1)
        for (int i = (int)adj[u].size() - 1; i > pi; i--) {
            int v = adj[u][i];
            if (v == parent_node[u]) continue;

            int base = assigned - 1;
            if (base <= 0) continue;

            if (target_processed) {
                 solve_moves(v, base, false, depth + 1);
            } else {
                if (process_child(v, base)) {
                    target_processed = true;
                    target_child = -2;
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(cin >> N)) return 0;

    for (int i = 1; i <= N; i++) {
        int k;
        cin >> k;
        adj[i].resize(k);
        for (int j = 0; j < k; j++) {
            cin >> adj[i][j];
        }
    }

    if (N == 1) {
        cout << "0 1" << endl;
        return 0;
    }

    build_tree(1, 0);
    calc_required(1);
    solve_moves(1, D[1], true, 0);

    cout << total_moves << " " << last_node << endl;

    return 0;
}
