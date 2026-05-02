#include<bits/stdc++.h>
using namespace std;

int n, m, a[1005], par[1005], sz[1005], vis[1005];

void init() {
    for (int i = 1; i <= 1e3; i++) {
        par[i] = i;
        sz[i] = 1;
    }
}

struct Query {
    int x, y, w;
} q[10005];

bool cmp(Query &l, Query &r) {
    return l.w < r.w;
}

int root(int u) {
    return (par[u] == u ? u : par[u] = root(par[u]));
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    init();
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> q[i].x >> q[i].y >> q[i].w;
    }
    sort(q, q + m, cmp);
    int cnt = 0;
    long long res = 0;
    for (int i = 0; i < m; i++) {
        int u = q[i].x;
        int v = q[i].y;
        if (!vis[v] && root(u) != root(v)) {
            Union(u, v);
            res += q[i].w;
            vis[v] = true;
            cnt++;
        }
    }
    cout << (cnt != n - 1 ? -1 : res);
    return 0;
}
