#include<bits/stdc++.h>
using namespace std;

#define int long long

int n;
map<int ,int> mp;
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n;
    int sum = 0;
    mp[0] = 1;
    for (int i = 1; i <= n; i++) {
        int k;
        cin >> k;
        sum += k;
        int temp = sum - i * (i + 1);
        mp[temp]++;
    }
    int res = 0;
    for (auto it = mp.begin(); it != mp.end(); it++) {
        res += it->second * (it->second - 1) / 2;
    }
    cout << res;
    return 0;
}
