#include<bits/stdc++.h>
using namespace std;

#define int long long

struct HASH {
    const int MOD = 1e9 + 7;
    const int BASE = 7;
    int n;
    string s;
    vector<int> h;
    vector<int> pow;
    HASH(const string &str) {
        s = str;
        n = s.length();
        h.resize(n);
        pow.resize(n);
        h[0] = s[0] - 'a' + 1;
        pow[0] = 1;
        for (int i = 1; i < n; i++) {
            h[i] = (h[i - 1] * BASE + (s[i] - 'a' + 1)) % MOD;
            pow[i] = (pow[i - 1] * BASE) % MOD;
        }
    }
    int get(int l, int r) {
        if (l == 0) {
            h[r] = (h[r] + MOD) % MOD;
            return h[r];
        }
        int res = (h[r] - h[l - 1] * pow[r - l + 1]) % MOD;
        res = (res + MOD) % MOD;
        return res;
    }
};

void solve() {
    string a, b;
    cin >> a >> b;
    int n = a.length();
    a += a;
    HASH hashA(a);
    HASH hashB(b);
    for (int i = 0; i < n; i++) {
//        int temp = hashA.get(i, i + n - 1);
//        int temp2 = hashB.get(0, n - 1);
        if (hashA.get(i, i + n - 1) == hashB.get(0, n - 1)) {
            cout << i << "\n";
            return;
        }
        //cout << temp << " " << temp2 << "\n";
    }
    cout << -1 << "\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
