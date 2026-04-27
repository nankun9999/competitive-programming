#include<bits/stdc++.h>
using namespace std;

const int LOG = 10;

int n, q, k, t;
vector<int> adj[1005];

struct LCA {
    int h[1005];
    int up[1005][20];
    void init(int n) {
        for (int i = 0; i <= n; i++) {
            h[i] = 0;
            for (int j = 0; j <= LOG; j++) {
                up[i][j] = 0;
            }
        }
    }
    
    void dfs(int u, int p) {
        for (int v : adj[u]) {
            if (v == p) {
                continue;
            }
            up[v][0] = u;
            for (int i = 1; i <= LOG; i++) {
                up[v][i] = up[up[v][i - 1]][i - 1];
            }
            h[v] = h[u] + 1;
            dfs(v, u);
        }
    }

    int get(int u, int v) {
        if (h[u] < h[v]) {
            swap(u, v);
        }
        int k = h[u] - h[v];
        for (int i = 0; i <= LOG; i++) {
            if ((k >> i) & 1) {
                u = up[u][i];
            }
        }
        if (u == v) {
            return u;
        }
        for (int i = LOG; i >= 0; i--) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    }
} lca;

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        adj[i].clear();
    }
    lca.init(n);
    for (int i = 1; i <= n; i++) {
        int m;
        cin >> m;
        for (int j = 0; j < m; j++) {
            int v;
            cin >> v;
            adj[i].push_back(v);
        }
    }
    lca.dfs(1, 0);
    cin >> t;
    while (t--) {
        int u, v;
        cin >> u >> v;
        cout << lca.get(u, v) << "\n";
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin >> q;
    for (int i = 0; i < q; i++) {
        cout << "Case " << i + 1 << ":\n";
        solve();
    }
    return 0;
}
