#include<bits/stdc++.h>
using namespace std;

#define int long long

string s;
int n;

struct HASH {
    const int MOD = 1e9 + 7;
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
            return h[r];
        }
        int res = (h[r] - h[l - 1] * pow[r - l + 1]) % MOD;
        res = (res + MOD) % MOD;
        return res;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> s;
    n = s.length();
    HASH hashS(s);
    for (int i = 0; i < n - 1; i++) {
        if (hashS.get(0, i) == hashS.get(n - i - 1, n - 1)) {
            cout << i + 1 << " ";
        }
    }
    return 0;
}
