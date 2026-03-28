#include<bits/stdc++.h>
using namespace std;

void setup() {
#ifndef ONLINE_JUDGE
    freopen("TASK.inp", "r", stdin);
    freopen("TASK.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

const int INF = 1e9 + 7;

int n, m, a[100005];
multiset<int> seg[400005];

multiset<int> Merge(multiset<int> l, multiset<int> r) {
    multiset<int> res;
    for (auto it : l) {
        res.insert(it);
    }
    for (auto it : r) {
        res.insert(it);
    }
    return res;
}

void build(int id, int l, int r) {
    if (l == r) {
        seg[id].insert(a[l]);
        return;
    }
    int mid = (l + r) / 2;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
    seg[id] = Merge(seg[id * 2], seg[id * 2 + 1]);
}

int get(int id, int l, int r, int u, int v, int k) {
    if (l > v || r < u) {
        return INF;
    }
    if (l >= u && r <= v) {
        auto it = seg[id].lower_bound(k);
        return (it == seg[id].end() ? INF : *it);
    }
    int mid = (l + r) / 2;
    return min(get(id * 2, l, mid, u, v, k), get(id * 2 + 1, mid + 1, r, u, v, k));
}

void update(int id, int l, int r, int pos, int k) {
    if (l == r) {
        auto it = seg[id].find(a[pos]);
        seg[id].erase(it);
        seg[id].insert(k);
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) {
        update(id * 2, l, mid, pos, k);
    } else {
        update(id * 2 + 1, mid + 1, r, pos, k);
    }
    auto it = seg[id].find(a[pos]);
    seg[id].erase(it);
    seg[id].insert(k);
}

int main() {
    setup();

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    build(1, 1, n);
    while (m--) {
        int type;
        cin >> type;
        if (type == 1) {
            int pos, k;
            cin >> pos >> k;
            update(1, 1, n, pos, k);
            a[pos] = k;
        } else {
            int u, v, k;
            cin >> u >> v >> k;
            int res = get(1, 1, n, u, v, k);
            cout << (res == INF ? -1 : res) << "\n";
        }
    }
    return 0;
}
