#include<bits/stdc++.h>
using namespace std;

int n, m, timer, num[100005], low[100005], numJoint, bridge;
bool joint[100005], vis[100005];
vector<pair<int, int>> adj[100005];

void dfs(int u, int p) {
    timer++;
    low[u] = num[u] = timer;
    int child = 0;
    for (auto pi : adj[u]) {
        int v = pi.first;
        int index = pi.second;
        if (vis[index]) {
            continue;
        }
        vis[index] = true;
        if (!num[v]) {
            dfs(v, u);
            low[u] = min(low[v], low[u]);
            child++;
            if (num[v] == low[v]) {
                bridge++;
            }
            if (p == 0) {
                if (child > 1) {
                    joint[u] = true;
                }
            } else {
                if (low[v] >= num[u]) {
                    joint[u] = true;
                }
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
    for (int i = 1; i <= n; i++) {
        if (joint[i]) {
            numJoint++;
        }
    }
    cout << numJoint << " " << bridge;
    return 0;
}
