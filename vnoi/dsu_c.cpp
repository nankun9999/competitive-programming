#include<bits/stdc++.h>
#define ii pair<int,int>
#define fi first
#define se second

using namespace std;

#define int long long

const int MAXN = 1e5 + 5;
const int MOD = 1e9 + 7;
const int INF = 1e9;

vector<int> adj[MAXN];
int n, m, sz[MAXN], par[MAXN], res[MAXN], add[MAXN];

int root(int u) {
    if (u == par[u]) {
        return u;
    } else {
        return par[u] = root(par[u]);
    }
}

void Union(int u, int v) {
    u = root(u), v = root(v);
    
    if (u == v) {
        return;
    }
    
    if (sz[u] < sz[v]) {
        swap(u, v);
    }
    
    par[v] = u;
    sz[u] += sz[v];
    
    for (int i = 0; i < adj[v].size(); i++) {
        int x = adj[v][i];
        adj[u].push_back(x);
        res[x] = res[x] + add[v] - add[u];
    }
    
    adj[v].clear();
}

signed main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    //freopen("TASK.INP", "r", stdin);
    //freopen("TASK.OUT", "w", stdout);
    
    cin >> n >> m;
    
    for (int i = 1; i <= n; i++) {
        par[i] = i;
        sz[i] = 1;
        adj[i].push_back(i);
    }
    
    while (m--) {
        string type;
        cin >> type;
        
        if (type == "join") {
            int u, v;
            cin >> u >> v;
            
            Union(u, v);
        } else if (type == "add") {
            int x, value;
            cin >> x >> value;
            
            add[root(x)] += value;
        } else {
            int x;
            cin >> x;
            
            cout << res[x] + add[root(x)] << "\n";
        }
    }

    return 0;
}
