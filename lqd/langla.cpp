#include<bits/stdc++.h>
using namespace std;

#define int long long

int n, q, up[200005][20], h[200005], dist[200005];
vector<pair<int, int>> adj[200005];

void dfs(int u, int p) {
    up[u][0] = p;
    for (int i = 1; i <= 18; i++) {
        up[u][i] = up[up[u][i - 1]][i - 1];
    }
    for (auto v : adj[u]) {
        if (v.first == p) {
            continue;
        }
        h[v.first] = h[u] + 1;
        dist[v.first] = dist[u] + v.second;
        dfs(v.first, u);
    }
}

int get(int u, int v) {
    if (h[u] < h[v]) {
        swap(u, v);
    }
    int k = h[u] - h[v];
    for (int i = 0; i <= 18; i++) {
        if ((k >> i) & 1) {
            u = up[u][i];
        }
    }
    if (u == v) {
        return u;
    }
    for (int i = 18; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

int cal(int u, int v) {
    return (dist[u] + dist[v]) - 2ll * dist[get(u, v)];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    dfs(1, -1);
    cin >> q;
    while (q--) {
        int a, b, c;
        cin >> a >> b >> c;
        int temp1 = get(a, b);
        int temp2 = get(b, c);
        int temp3 = get(a, c);
        cout << min({cal(temp1, a) + cal(temp1, b) + cal(temp1, c), 
                     cal(temp2, a) + cal(temp2, b) + cal(temp2, c), 
                     cal(temp3, a) + cal(temp3, b) + cal(temp3, c)}) << "\n";
    }
    return 0;
}
