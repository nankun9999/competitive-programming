#include<bits/stdc++.h>
using namespace std;

#define int long long

struct HASH {
    const int MOD = 1e9 + 3;
    const int BASE = 31;
    int n;
    string s;
    vector<int> h;
    vector<int> pow;
    HASH(const string &str) {
        s = str;
        n = s.length();
        h.resize(n);
        pow.resize(n);
        h[0] = s[0] - '0' + 1;
        pow[0] = 1;
        for (int i = 1; i < n; i++) {
            h[i] = (h[i - 1] * BASE + (s[i] - '0' + 1)) % MOD;
            pow[i] = (pow[i - 1] * BASE) % MOD;
        }
    }
    int get(int l, int r) {
        if (l == 0) {
            return h[r];
        }
        int res = (h[r] - h[l - 1] * pow[r - l + 1]) % MOD;
        res = (res + MOD) % MOD;
        return res;
    }
};

string s;
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    //freopen("TASK.INP", "r", stdin);
    cin >> s;
    HASH hs(s);
    int n = s.length();
    for (int len = 1; len <= n; len++) {
        int curr = hs.get(0, len - 1);
        bool flag = true;
        for (int i = 0; i < n; i += len) {
            if (curr != hs.get(i, i + len - 1) && i + len - 1 <= n - 1) {
                flag = false;
                break;
            }
        }
        int mod = n % len;
        if (mod != 0) {
            if (hs.get(0, mod - 1) != hs.get(n - mod, n - 1)) {
                flag = false;
            }
        }
        if (flag) {
            cout << s.substr(0, len);
            return 0;
        }
    }
    return 0;
}
