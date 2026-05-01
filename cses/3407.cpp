#include<bits/stdc++.h>
using namespace std;
 
int n, m, par[100005], sz[100005], res[200005];
 
struct Query {
    int x, y, id;
};
 
map<int, vector<Query>> mp;
 
void init() {
    for (int i = 1; i <= 1e5; i++) {
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
    sz[u] += sz[v];
    par[v] = u;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    init();
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        mp[w].push_back({u, v, i});
    }
    for (auto it = mp.begin(); it != mp.end(); it++) {
        for (auto i : it->second) {
            if (root(i.x) != root(i.y)) {
                res[i.id] = 1;
            }
        }
        for (auto i : it->second) {
            Union(i.x, i.y);
        }
    }
    for (int i = 0; i < m; i++) {
        cout << (res[i] ? "YES" : "NO") << "\n";
    }
    return 0;
}
