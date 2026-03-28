#include<bits/stdc++.h>
using namespace std;

#define int long long

const int MOD = 1e9 + 7;

int n, m, fact[3000005];

void pre() {
    fact[0] = 1;
    for (int i = 1; i <= 3e6; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
}

int binPow(int a, int b, int mod) {
    int res = 1;
    while (b > 0) {
        if (b & 1) {
            res = (res * a) % mod;
        }
        b >>= 1;
        a = (a * a) % mod;
    }
    return res;
}

int cal(int a, int b) {
    int res = fact[b];
    res = (res * binPow(fact[a], MOD - 2, MOD)) % MOD;
    res = (res * binPow(fact[b - a], MOD - 2, MOD)) % MOD;
    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    //freopen("TASK.INP", "r", stdin);
    cin >> n >> m;
    pre();   
    cout << cal(n - 1, n + m - 1);
    return 0;
}

