#include<bits/stdc++.h>
using namespace std;

int n, a[100005], bit[100005];

void update(int id, int val) {
    while (id <= 6e4) {
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

int getSum(int l, int r) {
    return get(r) - get(l - 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    freopen("TASK.INP", "r", stdin);
    cin >> n;
    long long res = 0;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        res += getSum(k + 1, 6e4);
        update(k, 1);
    }
    cout << res;
    return 0;
}
