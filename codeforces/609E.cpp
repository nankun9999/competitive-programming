#include<bits/stdc++.h>
using namespace std;

#define int long long

int n, m, sz[200005], par[200005], res, b[200005];
int up[200005][20], mx[200005][20], h[200005];
vector<pair<int, int>> adj[200005];

struct Edge {
    int x, y, w, index;
} a[200005];

bool cmp(Edge &l, Edge &r) {
    return l.w < r.w;
}

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
    for (auto i : adj[u]) {
        int v = i.first;
        int val = i.second;
        if (v == p) {
            continue;
        }
        up[v][0] = u;
        mx[v][0] = val;
        for (int i = 1; i <= 19; i++) {
            up[v][i] = up[up[v][i - 1]][i - 1];
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
    for (int i = 17; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            res = max({res, mx[u][i], mx[v][i]});
            u = up[u][i];
            v = up[v][i];
        }
    }
    return max({mx[u][0], mx[v][0], res});
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    init();
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> a[i].x >> a[i].y >> a[i].w;
        a[i].index = i;
    }
    sort(a, a + m, cmp);
    for (int i = 0; i < m; i++) {
        int u = a[i].x;
        int v = a[i].y;
        if (root(u) != root(v)) {
            Union(u, v);
            adj[u].push_back({v, a[i].w});
            adj[v].push_back({u, a[i].w});
            res += a[i].w;
        }
    }
    dfs(1, 0);
    for (int i = 0; i < m; i++) {
        b[a[i].index] = res - lca(a[i].x, a[i].y) + a[i].w;
    }
    for (int i = 0; i < m; i++) {
        cout << b[i] << "\n";
    }
    return 0;
}
