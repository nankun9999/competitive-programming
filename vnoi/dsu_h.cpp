#include<bits/stdc++.h>
using namespace std;

int n, q, nxt[200005], par[200005], sz[200005];

void init() {
    for (int i = 1; i <= 2e5 + 1; i++) {
        nxt[i] = i;
        par[i] = i;
        sz[i] = 1;
    }
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

int nextNode(int u) {
    return (nxt[u] == u ? u : nxt[u] = nextNode(nxt[u]));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    freopen("TASK.INP", "r", stdin);
    init();
    cin >> n >> q;
    while (q--) {
        int type, u, v;
        cin >> type >> u >> v;
        if (type == 1) {
            Union(u, v);
        } else if (type == 2) {
            int curr = nextNode(u);
            while (curr < v) {
                Union(curr, curr + 1);
                nxt[curr] = nextNode(curr + 1);
                curr = nxt[curr];
            } 
        } else {
            cout << (root(u) == root(v) ? "YES" : "NO") << "\n";
        }
    }
    return 0;
}
