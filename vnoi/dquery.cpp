#include<bits/stdc++.h>
using namespace std;

int n, q, bit[30005], res[200005], last[30005];
vector<int> v;
vector<pair<int, int>> query[200005];

void compress() {
    vector<int> v2 = v;
    sort(v2.begin(), v2.end());
    v2.erase(unique(v2.begin(), v2.end()), v2.end());
    for (int i = 0; i < n; i++) {
        int pos = lower_bound(v2.begin(), v2.end(), v[i]) - v2.begin();
        v[i] = pos + 1;
    }
}

void update(int id, int val) {
    while (id <= n) {
        bit[id] += val;
        id += id & (-id);
    }
}

int get(int id) {
    int res = 0;
    while (id > 0) {
        res += bit[id];
        id -= id & (-id);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    compress();
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        query[l].push_back({r, i});
    }
    for (int i = n; i >= 1; i--) {
        if (last[v[i - 1]] != 0) {
            update(last[v[i - 1]], -1);
        }
        update(i, 1);
        last[v[i - 1]] = i;
        for (auto qr : query[i]) {
            res[qr.second] = get(qr.first);
        }
    }
    for (int i = 0; i < q; i++) {
        cout << res[i] << "\n";
    }
    return 0;
}
