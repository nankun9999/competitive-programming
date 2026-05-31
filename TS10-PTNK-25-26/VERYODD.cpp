#include<bits/stdc++.h>
using namespace std;

#define int long long

int n;
vector<int> isPrime(1e6 + 5, true);
vector<int> prime;

void sieve() {
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= 1e6; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= 1e6; j += i) {
                isPrime[j] = false;
            }
        }
    }
    for (int i = 1; i <= 1e6; i++) {
        if (isPrime[i]) {
            prime.push_back(i);
        }
    }
}

void solve() {
    cin >> n;
    if (n & 1) {
        cout << 0 << "\n";
        return;
    }
    while (n % 2 == 0) {
        n /= 2;
    }
    int res = 1;
    for (int i : prime) {
        int cnt = 0;
        while (n % i == 0) {
            n /= i;
            cnt++;
        }
        res = res * (cnt / 2 + 1);
    }
    if (n != 1) {
        int temp = sqrt(n);
        if (temp * temp == n) {
            res *= 2;
        }
    }
    cout << res << "\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    //freopen("TASK.INP", "r", stdin);
    sieve();
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
