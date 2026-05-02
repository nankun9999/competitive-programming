#include<bits/stdc++.h>
using namespace std;

int n, m, up[100005][20], mx[100005][20];
int mn[100005][20], h[100005];
vector<pair<int, int>> adj[100005];

void init() {
    for (int i = 1; i <= 1e5; i++) {
        for (int j = 0; j <= 17; j++) {
            mn[i][j] = 1e9;
        }
    }
}

void dfs(int u, int p) {
    for (auto i : adj[u]) {
        int v = i.first;
        int w = i.second;
        if (v == p) {
            continue;
        }
        up[v][0] = u;
        mx[v][0] = w;
        mn[v][0] = w;
        for (int i = 1; i <= 17; i++) {
            up[v][i] = up[up[v][i - 1]][i - 1]; 
            mx[v][i] = max(mx[v][i - 1], mx[up[v][i - 1]][i - 1]);  
            mn[v][i] = min(mn[v][i - 1], mn[up[v][i - 1]][i - 1]); 
        }
        h[v] = h[u] + 1;
        dfs(v, u);
    }
}

pair<int, int> lca(int u, int v) {
    if (h[u] < h[v]) {
        swap(u, v);
    }
    int k = h[u] - h[v];
    int res1 = 0, res2 = 1e9;
    for (int i = 0; i <= 17; i++) {
        if ((k >> i) & 1) {
            res1 = max(res1, mx[u][i]);
            res2 = min(res2, mn[u][i]);
            u = up[u][i];
        }
    }
    if (u == v) {
        return {res1, res2};
    }
    for (int i = 17; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            res1 = max({res1, mx[u][i], mx[v][i]});
            res2 = min({res2, mn[u][i], mn[v][i]});
            u = up[u][i];
            v = up[v][i];
        }
    }
    return {max({mx[u][0], mx[v][0], res1}), min({mn[u][0], mn[v][0], res2})};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    //freopen("TASK.INP", "r", stdin);
    init();
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    dfs(1, 0);
    cin >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        auto res = lca(u, v);
        cout << res.second << " " << res.first << "\n";
    }
    return 0;
}
