#include<bits/stdc++.h>
using namespace std;

#define int long long

void setup() {
#ifndef ONLINE_JUDGE
    freopen("TASK.inp", "r", stdin);
    freopen("TASK.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

int n, q, c, prefA[200005], prefB[200005], a[200005], b[200005], cop[200005];
vector<pair<int, int>> v;
vector<int> diff;
// v[i].first : diff between B and A
//v[i].second : pos A and B before sorting

void pre() {
    v.resize(n);
    for (int i = 0; i < n; i++) {
        v[i].first = b[i] - a[i];
        v[i].second = i;
    }
    sort(v.begin(), v.end());
//    for (int i = 0; i < n; i++) {
//        cout << v[i].first << " " << v[i].second << "\n";
//    }
    diff.resize(n);
    for (int i = 0; i < n; i++) {
        diff[i] = v[i].first;
    }
    for (int i = 0; i < n; i++) {
        cop[i] = a[v[i].second];
    }
    prefA[0] = cop[0];
    for (int i = 1; i < n; i++) {
        prefA[i] = prefA[i - 1] + cop[i];
    }
    for (int i = 0; i < n; i++) {
        a[i] = cop[i];
    }
    for (int i = 0; i < n; i++) {
        cop[i] = b[v[i].second];
    }
    prefB[0] = cop[0];
    for (int i = 1; i < n; i++) {
        prefB[i] = prefB[i - 1] + cop[i];
    }
    for (int i = 0; i < n; i++) {
        b[i] = cop[i];
    }
}

void solve() {
    int pos = lower_bound(diff.begin(), diff.end(), c) - diff.begin();
    int sumA = 0, sumB = 0;
    if (pos != 0) {
        sumA = prefA[pos - 1] - prefA[0] + a[0];
    }
    if (pos != n) {
        sumB = (prefB[n - 1] - prefB[pos] + b[pos]) - c * (n - pos);
    }
    cout << sumA + sumB << "\n";
}

signed main() {
    setup();

    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    pre();
    while (q--) {
        cin >> c;
        solve();
    }
    return 0;
}
