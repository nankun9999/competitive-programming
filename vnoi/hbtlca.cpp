#include<bits/stdc++.h>
using namespace std;

int n, m, h[100005], up[100005][20], currRoot;
vector<int> adj[100005];

void dfs(int u, int p) {
    up[u][0] = p;
    for (int i = 1; i <= 17; i++) {
        up[u][i] = up[up[u][i - 1]][i - 1];
    }
    for (int v : adj[u]) {
        if (v == p) {
            continue;
        }
        h[v] = h[u] + 1;
        dfs(v, u);
    }
}

int lca(int u, int v) {
    if (h[u] < h[v]) {
        swap(u, v);
    }
    int k = h[u] - h[v];
    for (int i = 0; i <= 17; i++) {
        if ((k >> i) & 1) {
            u = up[u][i];
        }
    }
    if (u == v) {
        return u;
    }
    for (int i = 17; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

void init() {
    for (int i = 1; i <= 1e5; i++) {
        adj[i].clear();
        h[i] = 0;
    }
    for (int i = 1; i <= 1e5; i++) {
        for (int j = 0; j <= 17; j++) {
            up[i][j] = 0;
        }
    }
    currRoot = 1;
}

void solve() {
    init();
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0);
    cin >> m;
    while (m--) {
        char type;
        cin >> type;
        if (type == '!') {
            cin >> currRoot;
        } else {
            int u, v;
            cin >> u >> v;
            int temp1 = lca(u, currRoot);
            int temp2 = lca(v, currRoot);
            int temp3 = lca(u, v);
            if (max({h[temp1], h[temp2], h[temp3]}) == h[temp1]) {
                cout << temp1 << "\n";
            } else if ((max({h[temp1], h[temp2], h[temp3]}) == h[temp2])) {
                cout << temp2 << "\n";
            } else {
                cout << temp3 << "\n";
            }
        }
    }    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    while (cin >> n) {
        if (n == 0) {
            break;
        }
        solve();
    }
    return 0;
}
