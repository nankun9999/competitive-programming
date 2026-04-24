#include<bits/stdc++.h>
using namespace std;

int n, m, k, par[100005], sz[100005], cnt[100005];
vector<pair<int, int>> edge;
vector<string> res;
map<pair<int, int>, int> mp;
struct Query {
    string type;
    int x, y;
} a[200005];

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    init();
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        if (u > v) {
            swap(u, v);
        }
        edge.push_back({u, v});
    }
    for (int i = 0; i < k; i++) {
        cin >> a[i].type >> a[i].x >> a[i].y;
        if (a[i].x > a[i].y) {
            swap(a[i].x, a[i].y);
        }
        if (a[i].type == "cut") {
            mp[{a[i].x, a[i].y}]++;
        }
    }
    for (int i = 0; i < m; i++) {
        int u = edge[i].first;
        int v = edge[i].second;
        if (mp.find({u, v}) == mp.end()) {
            Union(u, v);
        }
    }
    for (int i = k - 1; i >= 0; i--) {
        int u = a[i].x;
        int v = a[i].y;
        if (a[i].type == "cut") {
            Union(u, v);
        } else {
            if (root(u) == root(v)) {
                res.push_back("YES");
            } else {
                res.push_back("NO");
            }
        }
    }
    for (int i = res.size() - 1; i >= 0; i--) {
        cout << res[i] << "\n";
    }
    return 0;
}
