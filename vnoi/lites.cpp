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

int n, m, seg[400005], lazy[400005];

void push(int id, int l, int r) {
    if (lazy[id] & 1) {
        int mid = (l + r) / 2;
        seg[id * 2] = (mid - l + 1) - seg[id * 2];
        seg[id * 2 + 1] = (r - mid) - seg[id * 2 + 1];
        lazy[id * 2]++;
        lazy[id * 2 + 1]++;
    }
    lazy[id] = 0;
}

int get(int id, int l, int r, int u, int v) {
    if (l > v || r < u) {
        return 0;
    }
    if (l >= u && r <= v) {
        return seg[id];
    }
    push(id, l, r);
    int mid = (l + r) / 2;
    return get(id * 2, l, mid, u, v) + get(id * 2 + 1, mid + 1, r, u, v);
}

void update(int id, int l, int r, int u, int v) {
    if (l > v || r < u) {
        return;
    }
    if (l >= u && r <= v) {
        seg[id] = (r - l + 1) - seg[id];
        lazy[id]++;
        return;
    }
    push(id, l, r);
    int mid = (l + r) / 2;
    update(id * 2, l, mid, u, v);
    update(id * 2 + 1, mid + 1, r, u, v);
    seg[id] = seg[id * 2] + seg[id * 2 + 1];
}

int main() {
    setup();

    cin >> n >> m;
    while (m--) {
        int type, l, r;
        cin >> type >> l >> r;
        if (type == 0) {
            update(1, 1, n, l, r);
        } else {
            cout << get(1, 1, n, l, r) << "\n";
        }
    }
    return 0;
}
