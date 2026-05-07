#include<bits/stdc++.h>
using namespace std;

int n, a[200005], bit[200005], last[200005];
int res[200005], tin[200005], tout[200005], cnt;
vector<pair<int, int>> query[200005];
vector<int> adj[200005];
vector<int> v;

void compress() {
    vector<int> v2 = v;
    sort(v2.begin(), v2.end());
    v2.erase(unique(v2.begin(), v2.end()), v2.end());
    for (int i = 0; i < n; i++) {
        int pos = lower_bound(v2.begin(), v2.end(), v[i]) - v2.begin();
        v[i] = pos + 1;
    }
}

void dfs(int u, int p) {
    cnt++;
    tin[u] = cnt;
    for (int v : adj[u]) {
        if (v == p) {
            continue;
        }
        dfs(v, u);
    }
    tout[u] = cnt;
} 

void update(int id, int val) {
    while (id <= n) {
        bit[id] += val;
        id += id & (-id);
    }
}

int get(int id) {
    int res = 0;
    while (id > 0) {
        res += bit[id];
        id -= id & (-id);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    //freopen("TASK.INP", "r", stdin);
    
    cin >> n;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    compress();
    dfs(1, 0);
    for (int i = 1; i <= n; i++) {
        a[tin[i]] = v[i - 1];
    }
    for (int i = 1; i <= n; i++) {
        query[tin[i]].push_back({tout[i], i});
    }
    for (int i = n; i >= 1; i--) {
        if (last[a[i]] != 0) {
            update(last[a[i]], -1);
        }
        last[a[i]] = i;
        update(i, 1);
        for (auto qr : query[i]) {
            res[qr.second] = get(qr.first);
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << res[i] << " ";
    }
    return 0;
}
