#include<bits/stdc++.h>
using namespace std;

#define int long long

int n;
map<int, int> mp;
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        mp[k]++;
    }
    int res = 0;
    for (auto it = mp.begin(); it != mp.end(); it++) {
        res += (it->second - 1) * it->second / 2;
    }
    cout << res;
    return 0;
}
