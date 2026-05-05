#include<bits/stdc++.h>
using namespace std;

#define int long long

int n, m, val[200005], dp[200005], prize[200005];
bool mark[200005];
vector<pair<int, int>> task;
int up[200005][20], mx[200005][20], h[200005];
vector<pair<int, int>> adj[200005];

void dfs(int u, int p) {
    for (auto id : adj[u]) {
        int v = id.first;
        int w = id.second;
        if (v == p) {
            continue;
        }
        up[v][0] = u;
        for (int i = 1; i <= 19; i++) {
            up[v][i] = up[up[v][i - 1]][i - 1];
        }
        mx[v][0] = w;
        for (int i = 1; i <= 19; i++) {
            mx[v][i] = max(mx[v][i - 1], mx[up[v][i - 1]][i - 1]);
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
    int res = max(val[u], val[v]);
    for (int i = 0; i <= 19; i++) {
        if ((k >> i) & 1) {
            res = max(res, mx[u][i]);
            u = up[u][i];
        }
    }
    if (u == v) {
        return res;
    }
    for (int i = 19; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            res = max({res, mx[u][i], mx[v][i]});
            u = up[u][i];
            v = up[v][i];
        }
    }
    return max({res, mx[u][0], mx[v][0]});
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    freopen("SHIP.inp", "r", stdin);
    freopen("SHIP.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, max(val[u], val[v])}); 
        adj[v].push_back({u, max(val[u], val[v])});
    }
    dfs(1, 0);
    cin >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        //cout << lca(u, v) << "\n";
        task.push_back({u, v});
    }
    for (int i = 2; i <= n; i++) {
        dp[i] = -1e18;
    }
    for (int i = 0; i < m; i++) {
        int u = task[i].first;
        int v = task[i].second;
        if (dp[u] != -1e18) {
            dp[v] = max(dp[v], dp[u] + lca(u, v));
        }
    }
    int res = 0;
    for (int i = 1; i <= n; i++) {
        res = max(res, dp[i]);
    }
    cout << res;
    return 0;
}
