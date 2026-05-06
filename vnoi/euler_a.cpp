#include<bits/stdc++.h>
using namespace std;

#define int long long

int n, q, tin[200005], tout[200005], cnt, seg[800005], a[200005], val[200005];
vector<int> adj[200005];

void dfs(int u, int p) {
    cnt++;
    tin[u] = cnt;
    val[cnt] = a[u];
    for (int v : adj[u]) {
        if (v == p) {
            continue;
        }
        dfs(v, u);
    }
    tout[u] = cnt;
}

void build(int id, int l, int r) {
    if (l == r) {
        seg[id] = val[l];
        return;
    }
    int mid = (l + r) / 2;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
    seg[id] = seg[id * 2] + seg[id * 2 + 1];
}

int get(int id, int l, int r, int u, int v) {
    if (l > v || r < u) {
        return 0;
    }
    if (l >= u && r <= v) {
        return seg[id];
    }
    int mid = (l + r) / 2;
    return get(id * 2, l, mid, u, v) + get(id * 2 + 1, mid + 1, r, u, v);
}

void update(int id, int l, int r, int pos, int k) {
    if (l == r) {
        seg[id] = k;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) {
        update(id * 2, l, mid, pos, k);
    } else {
        update(id * 2 + 1, mid + 1, r, pos, k);
    }
    seg[id] = seg[id * 2] + seg[id * 2 + 1];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    //freopen("TASK.INP", "r", stdin);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0);
    build(1, 1, n);
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int u, x;
            cin >> u >> x;
            update(1, 1, n, tin[u], x);
        } else {
            int u;
            cin >> u;
            cout << get(1, 1, n, tin[u], tout[u]) << "\n";
        }
    }
    return 0;
}
