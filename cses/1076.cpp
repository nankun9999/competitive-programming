#include<bits/stdc++.h>
using namespace std;

int n, k, a[200005], seg[800005], realVal[200005], val[200005];
vector<int> v;

void compress() {
    vector<int> v2 = v;
    sort(v2.begin(), v2.end());
    v2.erase(unique(v2.begin(), v2.end()), v2.end());
    for (int i = 0; i < n; i++) {
        int pos = lower_bound(v2.begin(), v2.end(), v[i]) - v2.begin();
        v[i] = pos + 1;
    }
}

int get(int id, int l, int r, int k) {
    if (seg[id] < k) {
        return -1;
    }
    if (l == r) {
        return l;
    }
    int mid = (l + r) / 2;
    if (seg[id * 2] >= k) {
        return get(id * 2, l, mid, k);
    }
    return get(id * 2 + 1, mid + 1, r, k - seg[id * 2]);
}

void update(int id, int l, int r, int pos, int k) {
    if (l == r) {
        seg[id] += k;
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
    
    cin >> n >> k;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        realVal[i] = v[i];
    }
    compress();
    for (int i = 0; i < n; i++) {
        val[v[i]] = realVal[i]; 
    }
    for (int i = 0; i < k; i++) {
        update(1, 1, n, v[i], 1);
    }
    int mid = (k & 1 ? k / 2 + 1 : k / 2);
    int pos = 0;
    cout << val[get(1, 1, n, mid)] << " ";
    for (int i = k; i < n; i++) {
        update(1, 1, n, v[pos], -1);
        update(1, 1, n, v[i], 1);
        cout << val[get(1, 1, n, mid)] << " ";
        pos++;
    }
    return 0;
}
