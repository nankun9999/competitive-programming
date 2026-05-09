#include<bits/stdc++.h>
using namespace std;

int n, m;
bool mark[100005];
int par[100005], sz[100005];
int up[100005][20], mn[100005][20],h[100005];
vector<pair<int, int>> adj[100005];

struct Edge {
    int x, y, val;
} q[100005];

bool cmp(Edge &left, Edge &right) {
    return left.val > right.val;
}

void init() {
    for (int i = 1; i <= 1e5; i++) {
        par[i] = i;
        sz[i] = 1;
    }
    for (int i = 1; i <= 1e5; i++) {
        for (int j = 0; j <= 17; j++) {
            mn[i][j] = 1e9;
        }
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
    for (auto pi : adj[u]) {
        int v = pi.first;
        int w = pi.second;
        if (v == p) {
            continue;
        }
        up[v][0] = u;
        for (int i = 1; i <= 17; i++) {
            up[v][i] = up[up[v][i - 1]][i - 1];
        }
        mn[v][0] = w;
        for (int i = 1; i <= 17; i++) {
            mn[v][i] = min(mn[v][i - 1], mn[up[v][i - 1]][i - 1]);
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
    int res = 1e9;
    for (int i = 0; i <= 17; i++) {
        if ((k >> i) & 1) {
            res = min(res, mn[u][i]);
            u = up[u][i];
        }
    }
    if (u == v) {
        return res;
    }
    for (int i = 17; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            res = min({res, mn[u][i], mn[v][i]});
            u = up[u][i];
            v = up[v][i];
        }
    }
    return min({res, mn[u][0], mn[v][0]});
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        q[i].x = u;
        q[i].y = v;
        q[i].val = w;
    }
    init();
    sort(q, q + m, cmp);
    for (int i = 0; i < m; i++) {
        int u = q[i].x;
        int v = q[i].y;
        int w = q[i].val;
        if (root(u) != root(v)) {
            Union(u, v);
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
            //cout << u << " " << v << " " << w << "\n";
        } else {
            mark[i] = true;
        }
    }
    dfs(1, 0);
    long long res = 0;
    for (int i = 0; i < m; i++) {
        int u = q[i].x;
        int v = q[i].y;
        int w = q[i].val;
        if (mark[i]) {
            res += lca(u, v) - w;
        }
    }
    cout << res;
    return 0;
}
