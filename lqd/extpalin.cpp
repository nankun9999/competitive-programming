#include<bits/stdc++.h>
using namespace std;

#define int long long

struct HASH {
    const int MOD = 1e9 + 9;
    const int BASE = 31;
    int n;
    string s;
    vector<int> h;
    vector<int> pow;
    HASH(const string &str) {
        s = str;
        n = s.length();
        pow.resize(n);
        h.resize(n);
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
        int res = h[r] - (h[l - 1] * pow[r - l + 1]) % MOD;
        res = (res + MOD) % MOD;
        return res;
    }
};

void solve() {
    string s;
    cin >> s;
    string rev = s;
    reverse(rev.begin(), rev.end());
    HASH hs(s);
    HASH hr(rev);
    int n = s.length();
    int revR = n - 1;
    for (int i = 0; i < n; i++) {
        if (hs.get(i, n - 1) == hr.get(0, revR)) {
            string add = "";
            if (i != 0) {
                add = s.substr(0, i);
            }
            reverse(add.begin(), add.end());
            cout << s + add << "\n";
            return;
        }
        revR--;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    //freopen("TASK.INP", "r", stdin);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
