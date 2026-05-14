#include<bits/stdc++.h>
using namespace std;

#define int long long

struct Hash {
    const int MOD = 1e9 + 7;
    const int BASE = 31;
    // dung cho upper + lower thi BASE = 53
    string s;
    int n;
    vector<int> pow;
    vector<int> h;
    
    Hash(const string &str) {
        s = str;
        n = s.length();
        h.resize(n);
        pow.resize(n);
        h[0] = s[0] - 'a' + 1;
        pow[0] = 1;
        for (int i = 1; i < n; ++i) {
            h[i] = (h[i - 1] * BASE + (s[i] - 'a' + 1)) % MOD;
            pow[i] = (pow[i - 1] * BASE) % MOD;
        }
    }
    int get(int l, int r) {
        if (l == 0) {
            return h[r];
        }
        int res = h[r] - (h[l - 1] * pow[r - l + 1]) % MOD;
        res = (res + MOD) % MOD;
        return res;
    }
};

string a, b;
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> a >> b;
    Hash hashA(a);
    Hash hashB(b);
    int len = b.length();
    for (int i = 0; i + len - 1 < a.length(); i++) {
        if (hashA.get(i, i + len - 1) == hashB.get(0, len - 1)) {
            cout << i + 1 << " ";
        }
    }
    return 0;
}
