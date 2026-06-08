#include<bits/stdc++.h>
using namespace std;

int q, pref[10000005];
bool vis[10000005];

void bfs() {
    queue<int> q;
    q.push(2);
    pref[2] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (2 * u + 1 <= 1e7 && !pref[2 * u + 1]) {
            q.push(2 * u + 1);
            pref[2 * u + 1] = 1;
        }
        if (3 * u <= 1e7 && !pref[3 * u]) {
            q.push(3 * u);
            pref[3 * u] = 1;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    //freopen("TASK.INP", "r", stdin);
    cin >> q;
    bfs();
    for (int i = 1; i <= 1e7; i++) {
        pref[i] = pref[i - 1] + pref[i];
    }
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << pref[r] - pref[l - 1] << "\n";
    }
    return 0;
}
