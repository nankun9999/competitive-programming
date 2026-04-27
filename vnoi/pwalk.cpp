#include<bits/stdc++.h>
using namespace std;

#define int long long

int n, q, h[10005], up[10005][20], dist[10005];
vector<pair<int, int>> adj[10005];

void dfs(int u, int p) {
    up[u][0] = p;
    for (int i = 1; i <= 17; i++) {
        up[u][i] = up[up[u][i - 1]][i - 1];
    }
    for (auto v : adj[u]) {
        if (v.first == p) {
            continue;
        }
        h[v.first] = h[u] + 1;
        dist[v.first] = dist[u] + v.second;
        dfs(v.first, u);
    }
}

int get(int u, int v) {
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> q;
    for (int i = 0; i < n - 1; i++) {
        int u, v, k;
        cin >> u >> v >> k;
        adj[u].push_back({v, k});
        adj[v].push_back({u, k});
    }
    dfs(1, -1);
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << dist[u] + dist[v] - 2ll * dist[get(u, v)] << "\n";
    }
    return 0;
}
