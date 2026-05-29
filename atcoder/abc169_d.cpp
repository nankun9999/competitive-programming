#include<bits/stdc++.h>
using namespace std;

#define int long long

int n, res;
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 2; i * i <= n; i++) {
        int cnt = 0;
        while (n % i == 0) {
            cnt++;
            n /= i;
        }
        for (int pow = 1; ; pow++) {
            if (pow * (pow + 1) / 2 > cnt) {
                res += (pow - 1);
                break;
            }
        }
    }
    if (n > 1) {
        res++;
    }
    cout << res;
    return 0;
}
