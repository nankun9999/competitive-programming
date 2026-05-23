#include<bits/stdc++.h>
using namespace std;

int n, m, timer, bridge, num[100005], low[100005];
bool mark[100005];
vector<pair<int, int>> adj[100005];

void dfs(int u, int p) {
    timer++;
    num[u] = low[u] = timer;
    for (auto pi : adj[u]) {
        int v = pi.first;
        int index = pi.second;
        if (v == p) {
            continue;
        }
        if (!num[v]) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > num[u]) {
                bridge++;
                mark[index] = true;
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
    cout << bridge << "\n";
    for (int i = 1; i <= m; i++) {
        if (mark[i]) {
            cout << i << " ";
        }
    }
    return 0;
}
