#include<bits/stdc++.h>
using namespace std;

int n, q, cnt[100005], h[100005], up[100005][20], res[100005];
vector<pair<int, int>> adj[100005];

void dfs(int u, int p) {
    up[u][0] = p;
    for (int i = 1; i <= 17; i++) {
        up[u][i] = up[up[u][i - 1]][i - 1];
    }
    for (auto v : adj[u]) {
        if (v.first == p) {
            continue;
        }
        h[v.first] = h[u] + 1;
        dfs(v.first, u);
    }
}

int get(int u, int v) {
    if (h[u] < h[v]) {
        swap(u, v);
    }
    int k = h[u] - h[v];
    for (int i = 0; i <= 17; i++) {
        if ((k >> i) & 1) {
            u = up[u][i];
        }
    }
    if (u == v) {
        return u;
    }
    for (int i = 17; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

void dfsSum(int u, int p) {
    for (auto v : adj[u]) {
        if (v.first == p) {
            continue;
        }
        dfsSum(v.first, u);
        cnt[u] += cnt[v.first];
        res[v.second] = cnt[v.first];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }
    dfs(1, 0);
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        cnt[u]++;
        cnt[v]++;
        cnt[get(u, v)] -= 2;
    }
    dfsSum(1, 0);
    for (int i = 0; i < n - 1; i++) {
        cout << res[i] << " ";
    }
    return 0;
}
