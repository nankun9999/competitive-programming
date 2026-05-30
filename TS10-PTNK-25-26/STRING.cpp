#include<bits/stdc++.h>
using namespace std;

int cnt[30];
string s;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> s;
    for (int i = 0; i < s.length(); i++) {
        cnt[s[i] - 'a']++;
    }
    int res = 0;
    for (int i = 0; i < 26; i++) {
        if (cnt[i] & 1) {
            res++;
        }
    }
    cout << max(res, 1);
    return 0;
}
