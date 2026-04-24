#include<bits/stdc++.h>
using namespace std;

int n, m, sz[300005], mx[300005], mn[300005], par[300005];

void init() {
    for (int i = 1; i <= 3e5; i++) {
        sz[i] = 1;
        mx[i] = i;
        par[i] = i;
        mn[i] = i;
    }
}

int root(int u) {
    return (u == par[u] ? u : par[u] = root(par[u]));
}

void Union(int u, int v) {
    u = root(u);
    v = root(v);
    if (u == v) {
        return;
    }
    if (sz[u] < sz[v]) {
        swap(u, v);
    }
    par[v] = u;
    sz[u] += sz[v];
    mx[u] = max(mx[u], mx[v]);
    mn[u] = min(mn[u], mn[v]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    init();
    cin >> n >> m;
    while (m--) {
        string type;
        cin >> type;
        if (type == "union") {
            int u, v;
            cin >> u >> v;
            Union(u, v);
        } else {
            int u;
            cin >> u;
            u = root(u);
            cout << mn[u] << " " << mx[u] << " " << sz[u] << "\n";
        }
    }
    return 0;
}
