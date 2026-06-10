#include<bits/stdc++.h>
using namespace std;

#define int long long

int n, q, seg[800005], lazy[800005], a[200005];

void push(int id, int l, int r) {
    int mid = (l + r) / 2;
    seg[id * 2] += (mid - l + 1) * lazy[id];
    seg[id * 2 + 1] += (r - mid) * lazy[id];
    lazy[id * 2] += lazy[id];
    lazy[id * 2 + 1] += lazy[id];
    lazy[id] = 0;
}

void build(int id, int l, int r) {
    if (l == r) {
        seg[id] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
    seg[id] = seg[id * 2] + seg[id * 2 + 1];
}

int get(int id, int l, int r, int u, int v) {
    if (l > v || r < u) {
        return 0;
    }
    if (l >= u && r <= v) {
        return seg[id];
    }
    int mid = (l + r) / 2;
    push(id, l, r);
    return get(id * 2, l, mid, u, v) + get(id * 2 + 1, mid + 1, r, u, v);
}

void update(int id, int l, int r, int u, int v, int k) {
    if (l > v || r < u) {
        return;
    }
    if (l >= u && r <= v) {
        seg[id] += k * (r - l + 1);
        lazy[id] += k;
        return;
    }
    int mid = (l + r) / 2;
    push(id, l, r);
    update(id * 2, l, mid, u, v, k);
    update(id * 2 + 1, mid + 1, r, u, v, k);
    seg[id] = seg[id * 2] + seg[id * 2 + 1];
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    //freopen("TASK.INP", "r", stdin);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    build(1, 1, n);
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int u, v, x;
            cin >> u >> v >> x;
            update(1, 1, n, u, v, x);
        } else {
            int k;
            cin >> k;
            cout << get(1, 1, n, k, k) << "\n";
        }
    }
    return 0;
}
