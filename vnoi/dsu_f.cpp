#include<bits/stdc++.h>
using namespace std;

int n, m, seg[4000005];

void build(int id, int l, int r) {
    if (l == r) {
        seg[id] = 1;
        return;
    }
    int mid = (l + r) / 2;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
    seg[id] = seg[id * 2] + seg[id * 2 + 1];
}

int get(int id, int l, int r, int pos, int k) {
    if (seg[id] < k) {
        return -1;
    }
    if (r < pos) {
        return -1;
    }
    if (l == r) {
        return l;
    }
    int mid = (l + r) / 2;
    int res = -1;
    if (seg[id * 2] >= k) {
        res = get(id * 2, l, mid, pos, k); 
    }
    if (res == -1) {
        res = get(id * 2 + 1, mid + 1, r, pos, k);
    }
    return res;
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n >> m;
    build(1, 1, n);
    while (m--) {
        string type;
        int u;
        cin >> type >> u;
        if (type == "-") {
            update(1, 1, n, u, 0);
        } else {
            cout << get(1, 1, n, u, 1) << "\n";
        }
    }
    return 0;
}
