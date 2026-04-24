#include<bits/stdc++.h>
using namespace std;

int n, m, q, par[100005], sz[100005];

void init() {
    for (int i = 1; i <= 1e5; i++) {
        par[i] = i;
        sz[i] = 1;
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

struct Edge {
    int x, y, w;
} numEdge[1000005], temp[1000005];

void solve() {
    cin >> n >> m >> q;
    for (int i = 1; i <= m; i++) {
        cin >> numEdge[i].x >> numEdge[i].y >> numEdge[i].w;
    }
    while (q--) {
        init();
        int s, cnt;
        cin >> s >> cnt;
        for (int i = 1; i <= m; i++) {
            temp[i] = numEdge[i];
        }
        for (int i = 0; i < cnt; i++) {
            int pos, newW;
            cin >> pos >> newW;
            temp[pos].w = newW;
        }
        for (int i = 1; i <= m; i++) {
            if (temp[i].w < temp[s].w) {
                Union(temp[i].x, temp[i].y);
            }
        }
        if (root(temp[s].x) == root(temp[s].y)) {
            cout << "YES" << "\n";
        } else {
            cout << "NO" << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    //freopen("TASK.INP", "r", stdin);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
