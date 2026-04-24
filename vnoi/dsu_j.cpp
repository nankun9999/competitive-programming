#include<bits/stdc++.h>
using namespace std;

struct Edge {
    int x, y, w;
} a[200005];

int n, m, par[200005], sz[200005];

bool cmp(Edge &l, Edge &r) {
    return l.w < r.w;
}

void init() {
    for (int i = 1; i <= 2e5; i++) {
        sz[i] = 1;
        par[i] = i;
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
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    //freopen("TASK.INP", "r", stdin);
    init();
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> a[i].x >> a[i].y >> a[i].w;
    }
    sort(a, a + m, cmp);
    long long res = 0;
    for (int i = 0; i < m; i++) {
        if (root(a[i].x) != root(a[i].y)) {
            res += a[i].w;
            Union(a[i].x, a[i].y);
        }
    }
    cout << res;
    return 0;
}
