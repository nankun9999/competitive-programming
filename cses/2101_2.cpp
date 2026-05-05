//using parallel binary search
#include<bits/stdc++.h>
using namespace std;

int n, m, q, l[200005], r[200005], res[200005];
vector<pair<int, int>> edge;
vector<pair<int, int>> query;
vector<int> bucket[200005];

struct DSU {
    int par[200005], sz[200005];
    void init() {
        for (int i = 1; i <= 2e5; i++) {
            sz[i] = 1;
            par[i] = i;
        }
    }
    int root(int u) {
        return (par[u] == u ? u : par[u] = root(par[u]));
    }
    void Union(int u, int v) {
        u = root(u), v = root(v);
        if (u == v) {
            return;
        }
        if (sz[u] < sz[v]) {
            swap(u, v);
        }
        par[v] = u;
        sz[u] += sz[v];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    //freopen("TASK.INP", "r", stdin);
    cin >> n >> m >> q;
    edge.push_back({0, 0});
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        edge.push_back({u, v});
    }
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        query.push_back({u, v});
        r[i] = m;
        l[i] = 0;
        res[i] = -1;
    }
    while (true) {
       bool flag = false;
       for (int i = 0; i <= m; i++) {
           bucket[i].clear();
       }
        for (int i = 0; i < q; i++) {
            if (l[i] <= r[i]) {
                int mid = (l[i] + r[i]) / 2;
                flag = true;
                bucket[mid].push_back(i);
            }
        }
        if (!flag) {
            break;
        }
        DSU dsu;
        dsu.init();
        for (int i = 0; i <= m; i++) {
            dsu.Union(edge[i].first, edge[i].second);
            for (int id : bucket[i]) {
                if (dsu.root(query[id].first) == dsu.root(query[id].second)) {
                    res[id] = i;
                    r[id] = i - 1;
                } else {
                    l[id] = i + 1;
                }
            }
        }
    }
    for (int i = 0; i < q; i++) {
        cout << res[i] << "\n";
    }
    return 0;
}
