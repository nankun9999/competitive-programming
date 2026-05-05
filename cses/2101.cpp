#include<bits/stdc++.h>
using namespace std;

int n, m, q, par[200005], sz[200005], currRoot;
int up[200005][20], mx[200005][20], h[200005];
vector<pair<int, int>> adj[200005];

struct Edge {
    int x, y, day;
} a[200005];

void init() {
    for (int i = 1; i <= 2e5; i++) {
        par[i] = i;
        sz[i] = 1;
    }
}

int root(int u) {
    return (u == par[u] ? u : par[u] = root(par[u]));
}

void Union(int u, int v) {
    u = root(u), v = root(v);
    if (u == v) {
        return;
    }
    if (sz[u] < sz[v]) {
        swap(u, v);
    }
    par[v] = u;
    sz[u] += sz[v];
}

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
    int res = 0;
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
    return max({mx[u][0], mx[v][0], res});
}

void debug() {
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= 19; j++) {
            cout << up[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    //freopen("TASK.INP", "r", stdin);
    init();
    cin >> n >> m >> q;
    for (int i = 0; i < m; i++) {
        cin >> a[i].x >> a[i].y;
        a[i].day = i + 1;
    }
    for (int i = 0; i < m; i++) {
        int u = a[i].x;
        int v = a[i].y;
        if (root(u) != root(v)) {
            Union(u, v);
            adj[u].push_back({v, a[i].day});
            adj[v].push_back({u, a[i].day});
            currRoot = u;
            //cout << u << " " << v << " " << a[i].day << "\n";
        }
    }
    dfs(currRoot, 0);
    //debug();
    while (q--) {
        int u, v;
        cin >> u >> v;
        if (root(u) != root(v)) {
            cout << -1 << "\n";
        } else {
            cout << lca(u, v) << "\n";
        }
    }
    return 0;
}
