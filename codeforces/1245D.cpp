#include<bits/stdc++.h>
using namespace std;

#define int long long

void setup() {
#ifndef ONLINE_JUDGE
    freopen("TASK.INP", "r", stdin);
    freopen("TASK.OUT", "w", stdout);
#endif 
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
}

int n, m, res, par[2005], sz[2005], k[2005];
vector<int> city;
vector<pair<int, int>> connect;
vector<pair<int, int>> node;

void init() {
    for (int i = 0; i <= 2e3; i++) {
        sz[i] = 1;
        par[i] = i;
    }
}

struct Edge {
    int x, y, w;
} q[5000005];

bool cmp(Edge &l, Edge &r) {
    return l.w < r.w;
}

int root(int u) {
    return (u == par[u] ? u : par[u] = root(par[u]));
}

void Union(int u, int v) {
    u = root(u);
    v = root(v);
    if (u == v) {
        return;
    }
    if (sz[u] < sz[v]) {
        swap(u, v);
    }
    sz[u] += sz[v];
    par[v] = u;
}

signed main() {
    setup();

    init();
    cin >> n;
    node.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> node[i].first >> node[i].second;
    }
    for (int i = 0; i < n; i++) {
        cin >> q[i].w;
        q[i].y = i + 1;
    }
    m = n;
    for (int i = 1; i <= n; i++) {
        cin >> k[i];
    }
    for (int i = 1; i <= n - 1; i++) {
        for (int j = i + 1; j <= n; j++) {
            int dist = abs(node[i].first - node[j].first) + abs(node[i].second - node[j].second);
            q[m].w = dist * (k[i] + k[j]);
            q[m].x = i;
            q[m].y = j;
            m++;
        }
    }
    sort(q, q + m, cmp);
    for (int i = 0; i < m; i++) {
        int u = q[i].x;
        int v = q[i].y;
        if (root(u) != root(v)) {
            Union(u, v); 
            res += q[i].w;
            if (u == 0) {
                city.push_back(v);
            } else {
                connect.push_back({u, v});
            }
        }
    }
    cout << res << "\n";
    cout << city.size() << "\n";
    for (int i : city) {
        cout << i << " ";
    }
    cout << "\n";
    cout << connect.size() << "\n";
    for (pair<int, int> p : connect) {
        cout << p.first << " " << p.second << "\n";
    }
    return 0;
}
