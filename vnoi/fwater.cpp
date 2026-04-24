#include<bits/stdc++.h>
using namespace std;
    
int n, m, par[305], sz[305];

void init() {
    for (int i = 0; i <= 300; i++) {
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
    par[v] = u;
    sz[u] += sz[v];
}

struct Edge {
    int x, y, w;
} a[100005];

bool cmp(Edge &l, Edge &r) {
    return l.w < r.w;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    //freopen("TASK.INP", "r", stdin);
    init();
    cin >> n;
    for (int i = 0; i < n; i++) {
        int temp;
        cin >> temp;
        a[i].x = 0;
        a[i].y = i + 1;
        a[i].w = temp;
    }
    m = n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int temp;
            cin >> temp;
            a[m].x = i;
            a[m].y = j;
            a[m].w = temp;
            m++;
        }
    }
//    for (int i = 0; i < m; i++) {
//        cout << a[i].x << " " << a[i].y << " " << a[i].w << "\n";
//    }
//    cout << "\n";
    long long res = 0;
    sort(a, a + m, cmp);
    for (int i = 0; i < m; i++) {
        if (root(a[i].x) != root(a[i].y)) {
            res += a[i].w;
            Union(a[i].x, a[i].y);
            //cout << a[i].x << " " << a[i].y << " " << a[i].w << "\n";
        }
    }
    cout << res;
    return 0;
}
