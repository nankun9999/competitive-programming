#include<bits/stdc++.h>
using namespace std;

int n, a[100005], q, par[100005];
vector<map<int, int>> cnt;

void init() {
    for (int i = 1; i <= 1e5; i++) {
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
    if (cnt[u].size() < cnt[v].size()) {
        swap(u, v);
    }
    for (auto it : cnt[v]) {
        cnt[u][it.first] += it.second;
    }
    par[v] = u;
    cnt[v].clear();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    init();
    cin >> n >> q;
    cnt.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        cnt[i][a[i]]++;
    }
    while (q--) {
        int type, u, v;
        cin >> type >> u >> v;
        if (type == 1) {
            Union(u, v);
        } else {
            u = root(u);
            cout << cnt[u][v] << "\n";
        }
    }
    return 0;
}
