#include<bits/stdc++.h>
using namespace std;

int n, m, timer, low[300005], num[300005], numBridge;
bool bridge[300005], vis[300005];
vector<pair<int, int>> adj[300005];

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
            if (low[v] == num[v]) {
                numBridge++;
                bridge[index] = true;
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
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, i + 1});
        adj[v].push_back({u, i + 1});
    }
    for (int i = 1; i <= n; i++) {
        if (!num[i]) {
            dfs(i, 0);
        }
    }
    cout << numBridge << "\n";
    for (int i = 1; i <= m; i++) {
        if (bridge[i]) {
            cout << i << " ";
        }
    }
    return 0;
}
