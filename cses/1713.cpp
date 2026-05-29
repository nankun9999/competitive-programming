#include<bits/stdc++.h>
using namespace std;

int n, d[1000005];

void sieve() {
    for (int i = 1; i <= 1e6; i++) {
        d[i]++;
        for (int j = i * 2; j <= 1e6; j += i) {
            d[j]++;
        }
    }
}

void solve() {
    cin >> n;
    cout << d[n] << "\n";
}
int main() {
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
