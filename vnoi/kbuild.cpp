#include<bits/stdc++.h>
using namespace std;

int n, m, timer, low[500005], num[500005], bridge;
bool vis[500005];
vector<pair<int, int>> adj[500005];

void dfs(int u, int p) {
    timer++;
    num[u] = low[u] = timer;
    for (auto pi : adj[u]) {
        int v = pi.first;
        int index = pi.second;
        if (vis[index]) {
            continue;
        }
        vis[index] = true;
        if (!num[v]) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > num[u]) {
                bridge++;
            }
        } else {
            low[u] = min(low[u], num[v]);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    //freopen("TASK.INP", "r", stdin);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, i + n});
        adj[v].push_back({u, i + n});
    }
    for (int i = 1; i <= n; i++) {
        if (!num[i]) {
            dfs(i, 0);
        }
    }
    cout << bridge;
    return 0;
}
