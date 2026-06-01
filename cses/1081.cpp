#include<bits/stdc++.h>
using namespace std;

int n, occ[1000005];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        occ[k]++;        
    }
    for (int i = 1e6; i >= 1; i--) {
        int cnt = 0;
        for (int j = i; j <= 1e6; j += i) {
            cnt += occ[j];
        }
        if (cnt > 1) {
            cout << i;
            return 0;
        }
    }
    return 0;
}
