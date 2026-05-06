#include<bits/stdc++.h>
using namespace std;

#define int long long

int n, q, tin[200005], tout[200005], cnt, bit[200005], a[200005];
vector<int> adj[200005];

void dfs(int u, int p) {
    cnt++;
    tin[u] = cnt;
    for (int v : adj[u]) {
        if (v == p) {
            continue;
        }
        dfs(v, u);
    }
    tout[u] = cnt;
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

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
    for (int i = 1; i <= n; i++) {
        update(tin[i], a[i]);
        if (tout[i] + 1 <= n) {
            update(tout[i] + 1, -a[i]);
        }
    }
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int u, x;
            cin >> u >> x;
            int delta = x - a[u];
            a[u] = x;
            update(tin[u], delta);
            if (tout[u] + 1 <= n) {
                update(tout[u] + 1, -delta);
            }
        } else {
            int u;
            cin >> u;
            cout << get(tin[u]) << "\n";
        }
    }
    return 0;
}
