#include<bits/stdc++.h>
using namespace std;

int n, m, low[100005], num[100005], timer, bridge, numJoint;
bool joint[100005];
vector<int> adj[100005];

void dfs(int u, int p) {
    int child = 0;
    timer++;
    num[u] = low[u] = timer;
    for (int v : adj[u]) {
        if (v == p) {
            continue;
        }
        if (!num[v]) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            child++;
            if (num[v] == low[v]) {
                bridge++;
            }
            if (p == 0) {
                if (child > 1) {
                    joint[u] = true;
                }
            } else if (low[v] >= num[u]) {
                joint[u] = true;
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
        adj[u].push_back(v);
        adj[v].push_back(u);
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
