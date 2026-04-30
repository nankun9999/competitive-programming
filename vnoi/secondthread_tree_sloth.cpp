#include<bits/stdc++.h>
using namespace std;

int n, q, up[300005][20], h[300005];
vector<int> adj[300005];

void dfs(int u, int p) {
    up[u][0] = p;
    for (int i = 1; i <= 19; i++) {
        up[u][i] = up[up[u][i - 1]][i - 1];
    }
    for (int v : adj[u]) {
        if (v != p) {
            h[v] = h[u] + 1;
            dfs(v, u);
        }
    }
}

int lca(int u, int v) {
    if (h[u] < h[v]) {
        swap(u, v);
    }
    int k = h[u] - h[v];
    for (int i = 0; i <= 19; i++) {
        if ((k >> i) & 1) {
            u = up[u][i];
        }
    }
    if (u == v) {
        return u;
    }
    for (int i = 19; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

int get(int u, int k) {
    for (int i = 0; i <= 19; i++) {
        if ((k >> i) & 1) {
            u = up[u][i];
        }
    }
    return u;
}

int dist(int u, int v) {
    return h[u] + h[v] - 2ll * h[lca(u, v)];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0);
    cin >> q;
    while (q--) {
        int a, b, c;
        cin >> a >> b >> c;
        int distAB = dist(a, b);
        if (c >= distAB) {
            cout << b;
        } else if (c <= dist(a, lca(a, b))) {
            cout << get(a, c);
        } else {
            cout << get(b, dist(a, b) - c);
        }
        cout << "\n";
    }
    return 0;
}
