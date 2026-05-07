#include<bits/stdc++.h>
using namespace std;

struct FenwickTree {
    int n, bit[100005];
    
    void init(int sz) {
        n = sz;
        for (int i = 1; i <= n; i++) {
            bit[i] = 0;
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
    
    int getSum(int l, int r) {
        return get(r) - get(l - 1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    return 0;
}
