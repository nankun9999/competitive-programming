#include<bits/stdc++.h>
using namespace std;

#define int long long

int n, q, a[100005], seg[400005];

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
    return get(id * 2, l, mid, u, v) + get(id * 2 + 1, mid + 1, r, u, v);
}

void update(int id, int l, int r, int pos, int k) {
    if (l == r) {
        seg[id] = k;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) {
        update(id * 2, l, mid, pos, k);
    } else {
        update(id * 2 + 1, mid + 1, r, pos, k);
    }
    seg[id] = seg[id * 2] + seg[id * 2 + 1];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> q;
    while (q--) {
        int type, x, y;
        cin >> type >> x >> y;
        if (type == 1) {
            update(1, 1, n, x, y);
        } else {
            cout << get(1, 1, n, x, y) << "\n";
        }
    }
    
    return 0;
}
