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

long long n;
int main() {
    setup();

    cin >> n;
    cout << n << " ";
    while (n > 1) {
        if (n & 1) {
            n = n * 3 + 1;
        } else {
            n /= 2;
        }
        cout << n << " ";
    }
    return 0;
}
