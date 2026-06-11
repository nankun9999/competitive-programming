#include<bits/stdc++.h>
using namespace std;

#define ii pair<int, int>
#define int long long

int n, m, dist[100005];
vector<ii> adj[100005];
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }
    for (int i = 2; i <= 1e5; i++) {
        dist[i] = 1e18;
    }
    priority_queue<ii, vector<ii>, greater<ii>> pq;
    pq.push({0, 1});
    while (!pq.empty()) {
        int u = pq.top().second;
        int w = pq.top().first;
        pq.pop();
        if (dist[u] != w) {
            continue;
        }
        for (auto pi : adj[u]) {
            int v = pi.first;
            int w2 = pi.second;
            if (dist[v] > w + w2) {
                dist[v] = w + w2;
                pq.push({dist[v], v});
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << dist[i] << " ";
    }
    return 0;
}
