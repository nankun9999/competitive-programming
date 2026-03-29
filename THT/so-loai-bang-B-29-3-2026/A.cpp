#include<bits/stdc++.h>
using namespace std;

void setup() {
#ifndef ONLINE_JUDGE
    freopen("TASK.inp", "r", stdin);
    freopen("TASK.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

long long temp;
__int128 res, n;

string convert() {
    string s;
    while (res > 0) {
        s += (res % 10) + '0';
        res /= 10;
    }
    reverse(s.begin(), s.end());
    return s;
}

int main() {
    setup();

    cin >> temp;
    res, n = temp;
    if (n % 2) {
        res = n * n + 1;
        res /= 2;
    } else {
        res = 2 * n * n + 2;
    }
    cout << convert();
    return 0;
}
