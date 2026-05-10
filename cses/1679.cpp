#include<bits/stdc++.h>
using namespace std;

int n, m, inDeg[100005];
vector<int> adj[100005];
vector<int> topo;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        inDeg[v]++;
    }
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (!inDeg[i]) {
            q.push(i);
            topo.push_back(i);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            inDeg[v]--;
            if (!inDeg[v]) {
                q.push(v);
                topo.push_back(v);
            }
        }
    }
    if (topo.size() == 0) {
        cout << "IMPOSSIBLE";
        return 0;
    }
    for (int u : topo) {
        cout << u << " ";
    }
    return 0;
}
