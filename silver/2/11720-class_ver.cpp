#include <iostream>
#include <vector>

using namespace std;

class Graph {
private:
    vector<vector<int>> adj;
    vector<bool> visited;
    int n;

    void dfs(int node) {
        visited[node] = true;
        for (int i = 1; i <= n; i++) {
            if (adj[node][i] && !visited[i]) {
                dfs(i);
            }
        }
    }

public:
    Graph(int vertices) : n(vertices) {
        adj.resize(n + 1, vector<int>(n + 1, 0));
        visited.resize(n + 1, false);
    }

    void addEdge(int u, int v) {
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    int countComponents() {
        int count = 0;
        for (int i = 1; i <= n; i++) {
            if (!visited[i]) {
                dfs(i);
                count++;
            }
        }
        return count;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;

    Graph graph(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph.addEdge(u, v);
    }

    cout << graph.countComponents() << '\n';
    return 0;
}
