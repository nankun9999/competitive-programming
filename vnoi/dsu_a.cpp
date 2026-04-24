#include<bits/stdc++.h>
using namespace std;

int n, m, par[100005], sz[100005];

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
}

void init() {
    for (int i = 1; i <= 1e5; i++) {
        par[i] = i;
        sz[i] = 1;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n >> m;
    init();
    while (m--) {
        string type;
        int u, v;
        cin >> type >> u >> v;
        if (type == "union") {
            Union(u, v);
        } else {
            cout << (root(u) == root(v) ? "YES" : "NO") << "\n";
        }
    }
    return 0;
}
