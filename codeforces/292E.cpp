#include <bits/stdc++.h>
using namespace std;

int n, m, a[100005], b[100005], seg[400005];

void push(int id) {
    if (seg[id] == 1e9) {
        return;
    }
    seg[id * 2] = seg[id];
    seg[id * 2 + 1] = seg[id];
    seg[id] = 1e9;
}

int get(int id, int l, int r, int pos) {
    if (l == r) {
        return seg[id];
    }
    int mid = (l + r) / 2;
    push(id);
    if (pos <= mid) {
        return get(id * 2, l, mid, pos);
    } else {
        return get(id * 2 + 1, mid + 1, r, pos);
    }
}

void update(int id, int l, int r, int u, int v, int k) {
    if (l > v || r < u) {
        return;
    }
    if (l >= u && r <= v) {
        seg[id] = k;
        return;
    }
    push(id);
    int mid = (l + r) / 2;
    update(id * 2, l, mid, u, v, k);
    update(id * 2 + 1, mid + 1, r, u, v, k);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n >> m;
    for (int i = 1; i <= 4 * n; i++) {
        seg[i] = 1e9;
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    while (m--) {
        int type;
        cin >> type;
        if (type == 1) {
            int x, y, k;
            cin >> x >> y >> k;
            update(1, 1, n, y, y + k - 1, x - y);
        } else {
            int k;
            cin >> k;
            int pos = get(1, 1, n, k);
            if (pos == 1e9) {
                cout << b[k] << "\n";
            } else {
                cout << a[pos + k] << "\n";
            }
        }
    }
    return 0;
}
