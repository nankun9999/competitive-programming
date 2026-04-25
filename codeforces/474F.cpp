#include<bits/stdc++.h>
using namespace std;

int n, q, a[100005];

struct Node {
    int gcd, cnt;
} seg[400005];

Node merge(Node l, Node r) {
    if (l.gcd == 0) {
        return r;
    }
    if (r.gcd == 0) {
        return l;
    }
    Node res;
    if (l.gcd == r.gcd) {
        res.gcd = l.gcd;
        res.cnt = l.cnt + r.cnt;
    } else if (l.gcd % r.gcd == 0) {
        res = r;
    } else if (r.gcd % l.gcd == 0) {
        res = l;
    } else {
        res.gcd = __gcd(l.gcd, r.gcd);
        res.cnt = 0;
    }
    return res;
}

void build(int id, int l, int r) {
    if (l == r) {
        seg[id] = {a[l], 1};
        return;
    }
    int mid = (l + r) / 2;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
    seg[id] = merge(seg[id * 2], seg[id * 2 + 1]);
}

Node get(int id, int l, int r, int u, int v) {
    if (l > v || r < u) {
        return {0, 0};
    }
    if (l >= u && r <= v) {
        return seg[id];
    }
    int mid = (l + r) / 2;
    return merge(get(id * 2, l, mid, u, v), get(id * 2 + 1, mid + 1, r, u, v));
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    build(1, 1, n);
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << (r - l + 1) - get(1, 1, n, l, r).cnt << "\n";
    }
    return 0;
}
