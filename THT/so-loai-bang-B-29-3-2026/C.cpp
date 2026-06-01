#include<bits/stdc++.h>
#define int long long
using namespace std;

vector<bool> prime(127, true);
int memo[16][16][126];

void sieve() {
    prime[0] = false;
    prime[1] = false;
    for (int i = 2; i * i <= 126; i++) {
        if (prime[i]) {
            for (int j = i * i; j <= 126; j += i) {
                prime[j] = false;
            }
        }
    }
}

int dp(vector<int>& arr, int pos, bool tight, int sum) {
    if (pos == (int)arr.size()) {
        return prime[sum];
    }
    if (memo[pos][(int)arr.size()][sum] >= 0 && !tight) {
        return memo[pos][(int)arr.size()][sum];
    }
    int limit = (tight ? arr[pos] : 9);
    int ans = 0;
    for (int i = 0; i <= limit; i++) {
        int npos = pos + 1;
        bool ntight = tight && i == limit;
        int nsum = sum + i;
        ans += dp(arr, npos, ntight, nsum);
    }
    if (!tight) {
        memo[pos][(int)arr.size()][sum] = ans;
    }
    return ans;
}

int f(int n) {
    vector<int> arr;
    while (n > 0) {
        arr.push_back(n % 10);
        n /= 10;
    }
    reverse(arr.begin(), arr.end());
    return dp(arr, 0, true, 0);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    sieve();
    memset(memo, -1, sizeof(memo));
    vector<int> sq(1e7 + 1);
    for (int i = 1; i <= 1e7; i++) {
        int sum = 0, n = i * i;
        while (n > 0) {
            sum += n % 10;
            n /= 10;
        }
        if (prime[sum]) {
            sq[i] = sq[i - 1] + 1;
        } else {
            sq[i] = sq[i - 1];
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        int A = a, B = b;
        a = ceil(sqrt(a));
        b = (int)sqrt(b);
        cout << (f(B) - f(A - 1)) - max(0LL, sq[b] - sq[a - 1]) << "\n";
    }

    return 0;
}
