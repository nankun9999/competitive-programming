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

bool check(int n) {
    int cnt = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            cnt++;
            cnt += (n / i != i);
        }
    }
    return cnt >= 500;
}

int main() {
    setup();

    int sum = 1;
    int curr = 2;
    while (!check(sum)) {
        sum += curr;
        curr++;
    }
    cout << sum;
    return 0;
}
