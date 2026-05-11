#include<bits/stdc++.h>
using namespace std;

struct DSU {
  int par[100005], sz[100005];
  void init() {
    for (int i = 1; i <= 1e5; i++) {
        par[i] = i;
        sz[i] = 1;
    }
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
} dsu;

int n, m;
struct Edge {
    int x, y, val;
} q[100005];

bool cmp(Edge &left, Edge &right) {
    return left.val < right.val;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    dsu.init();
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> q[i].x >> q[i].y >> q[i].val;
    }
    sort(q, q + m, cmp);
    long long res = 0;
    for (int i = 0; i < m; i++) {
        int u = q[i].x;
        int v = q[i].y;
        int w = q[i].val;
        if (dsu.root(u) != dsu.root(v)) {
            dsu.Union(u, v);
            res += w;
        }
    }
    cout << res;
    return 0;
}
