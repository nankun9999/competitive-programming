#include<bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

int n, m, a[100005], seg[400005], lazy[400005];
vector<pair<int, int>> q;
vector<int> v;

void push(int id) {
    seg[id * 2] += lazy[id];
    seg[id * 2 + 1] += lazy[id];
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
    seg[id] = max(seg[id * 2], seg[id * 2 + 1]);
}

int get(int id, int l, int r, int u, int v) {
    if (l > v || r < u) {
        return -1e9;
    }
    if (l >= u && r <= v) {
        return seg[id];
    }
    push(id);
    int mid = (l + r) / 2;
    return max(get(id * 2, l, mid, u, v), get(id * 2 + 1, mid + 1, r, u, v));
}

void update(int id, int l, int r, int u, int v, int k) {
    if (l > v || r < u) {
        return;
    }
    if (l >= u && r <= v) {
        seg[id] += k;
        lazy[id] += k;
        return;
    }
    int mid = (l + r) / 2;
    push(id);
    update(id * 2, l, mid, u, v, k);
    update(id * 2 + 1, mid + 1, r, u, v, k);
    seg[id] = max(seg[id * 2], seg[id * 2 + 1]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        q.push_back({l, r});
    }
    build(1, 1, n);
    int res = 0, pos = -1;
    for (int i = 1; i <= n; i++) {
        int mn = a[i];
        for (auto p : q) {
            if (i >= p.first && i <= p.second) {
                update(1, 1, n, p.first, p.second, -1);
                mn--;
            }
        }
        int mx = get(1, 1, n, 1, n);
        if (mx - mn > res) {
            res = mx - mn;
            pos = i;
        }
        for (auto p : q) {
            if (i >= p.first && i <= p.second) {
                update(1, 1, n, p.first, p.second, 1);
            }
        }
    }
    for (int i = 0; i < q.size(); i++) {
        if (pos >= q[i].first && pos <= q[i].second) {
            v.push_back(i + 1);
        }
    }
    cout << res << "\n";
    cout << v.size() << "\n";
    for (auto i : v) {
        cout << i << " ";
    }
    return 0;
}
