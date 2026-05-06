#include<bits/stdc++.h>
using namespace std;

const int MAXN = 3e5;

int n, q, up[MAXN + 5][20], h[300005], seg[MAXN * 4 + 5];
vector<int> adj[MAXN + 5];

void dfs(int u, int p) {
    up[u][0] = p;
    for (int i = 1; i <= 19; i++) {
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

void build(int id, int l, int r) {
    if (l == r) {
        seg[id] = l;
        return;
    }
    int mid = (l + r) / 2;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
    seg[id] = lca(seg[id * 2], seg[id * 2 + 1]);
}

int get(int id, int l, int r, int u, int v) {
    if (l > v || r < u) {
        return 0;
    }
    if (l >= u && r <= v) {
        return seg[id];
    }
    int mid = (l + r) / 2;
    int left = get(id * 2, l, mid, u, v);
    int right = get(id * 2 + 1, mid + 1, r, u, v);
    if (left == 0) {
        return right;
    }
    if (right == 0) {
        return left;
    }
    return lca(left, right);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    //freopen("TASK.INP", "r", stdin);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0);
    build(1, 1, n);
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << get(1, 1, n, u, v) << "\n";
    }
    return 0;
}
