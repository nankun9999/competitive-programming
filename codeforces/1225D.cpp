#include<bits/stdc++.h>
using namespace std;

int n, k, spf[100005];
long long res;
map<vector<pair<int, int>>, int> mp;

void sieve() {
    for (int i = 1; i <= 1e5; i++) {
        spf[i] = i;
    } 
    for (int i = 2; i * i <= 1e5; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j <= 1e5; j += i) {
                if (spf[j] == j) {
                    spf[j] = i;
                }
            }
        }
    }
}

void process(int x) {
    vector<pair<int, int>> curr;
    vector<pair<int, int>> need;
    while (x > 1) {
        int p = spf[x];
        int cnt = 0;
        while (x % p == 0) {
            x /= p;
            cnt++;
        }
        cnt %= k;
        if (!cnt) {
            continue;
        }
        curr.push_back({p, cnt});
        need.push_back({p, k - cnt});
    }
    if(mp.find(need) != mp.end()) {
        res += mp[need];
    }
    mp[curr]++;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    sieve();
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        process(a);
    }
    cout << res;
    return 0;
}
