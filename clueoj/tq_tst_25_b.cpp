#include<bits/stdc++.h>
using namespace std;

int n, k, seg[400005], res;
vector<int> a, b;
vector<int> adj[11];

void compress() {
    vector<int> temp = a;
    sort(temp.begin(), temp.end());
    temp.erase(unique(temp.begin(), temp.end()), temp.end());
    for (int i = 0; i < n; i++) {
        int pos = lower_bound(temp.begin(), temp.end(), a[i]) - temp.begin();
        a[i] = pos + 1;
    }
}

int get(int id, int l, int r, int u, int v) {
    if (l > v || r < u) {
        return 0;
    }
    if (l >= u && r <= v) {
        return seg[id];
    }
    int mid = (l + r) / 2;
    return max(get(id * 2, l, mid, u, v), get(id * 2 + 1, mid + 1, r, u, v));
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
    seg[id] = max(seg[id * 2], seg[id * 2 + 1]);
}

void solve(int x) {
    fill_n(seg, n * 4 + 5, 0);
    vector<int> v = adj[x];
    for (int i = 0; i < v.size(); i++) {
        int curr = get(1, 1, n, 1, v[i] - 1);
        update(1, 1, n, v[i], curr + 1);
    }
    res = max(res, get(1, 1, n, 1, 1e5));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    //freopen("TASK.INP", "r", stdin);
    cin >> n >> k;
    a.resize(n);
    b.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    compress();
    for (int i = 0; i < n; i++) {
        adj[b[i]].push_back(a[i]);
    }
    for (int i = 1; i <= k; i++) {
        solve(i);
    }
    cout << res;
    return 0;
}
