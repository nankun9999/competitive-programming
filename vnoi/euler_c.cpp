#include<bits/stdc++.h>
using namespace std;

#define int long long

struct Edge {
    int x, y, val;
} edges[200005];

int n, q;
int tin[200005], tout[200005], cnt;
int up[200005][20], h[200005];
int bit[200005];
vector<pair<int, int>> adj[200005];

void dfs(int u, int p) {
    up[u][0] = p;
    for (int i = 1; i <= 18; i++) {
        up[u][i] = up[up[u][i - 1]][i - 1];
    }
    cnt++;
    tin[u] = cnt;
    for (auto pi : adj[u]) {
        int v = pi.first;
        int w = pi.second;
        if (v == p) {
            continue;
        }
        h[v] = h[u] + 1;
        dfs(v, u);
    }
    tout[u] = cnt;
}

int lca(int u, int v) {
    if (h[u] < h[v]) {
        swap(u, v);
    }
    int k = h[u] - h[v];
    for (int i = 0; i <= 18; i++) {
        if ((k >> i) & 1) {
            u = up[u][i];
        }
    }
    if (u == v) {
        return u;
    }
    for (int i = 18; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

void update(int id, int val) {
    while (id <= n) {
        bit[id] += val;
        id += id & (-id);
    }
}

int get(int id) {
    int res = 0;
    while (id > 0) {
        res += bit[id];
        id -= id & (-id);
    }
    return res;
}

void addRange(int l, int r, int val) {
    update(l, val);
    update(r + 1, -val);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        edges[i].x = u;
        edges[i].y = v;
        edges[i].val = w;
    }
    dfs(1, 0);
    for (int i = 0; i < n - 1; i++) {
        int u = edges[i].x;
        int v = edges[i].y;
        int w = edges[i].val;
        if (h[u] > h[v]) {
            swap(u, v);
        }
        addRange(tin[v], tout[v], w);
    }
    cin >> q;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int i, newW;
            cin >> i >> newW;
            i--;
            int u = edges[i].x;
            int v = edges[i].y;
            int w = edges[i].val;
            int delta = newW - w;
            if (h[u] > h[v]) {
                swap(u, v);
            }
            addRange(tin[v], tout[v], delta);
            edges[i].val = newW;
        } else {
            int u, v;
            cin >> u >> v;
            int l = lca(u, v);
            cout << get(tin[v]) + get(tin[u]) - 2ll * get(tin[l]) << "\n";
        }
    }
    return 0;
}
