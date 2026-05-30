#include<bits/stdc++.h>
using namespace std;

int n, m, k, wolf[505][505], human[505][505];
pair<int, int> endPos;
vector<int> d;
vector<pair<int, int>> moves;
char a[505][505];
int dx[] = {0, -1, 1, 0};
int dy[] = {-1, 0, 0, 1};

void prep() {
    for (int i : d) {
        for (int x = -5; x <= 5; x++) {
            for (int y = -5; y <= 5; y++) {
                if (x * x + y * y == i) {
                    moves.push_back({x, y});
                }
            }
        }
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j] == 't') {
                endPos.first = i;
                endPos.second = j;
                break;
            }
        }
    }
}

void bfsWolf() {
    queue<pair<int, int>> q;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j] != 'w') {
                wolf[i][j] = 1e9;
            } else {
                q.push({i, j});
            }
        }
    }
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int newx = x + dx[i];
            int newy = y + dy[i];
            if (newx > 0 && newx <= m && newy > 0 && newy <= n) {
                if (a[newx][newy] != '#' && wolf[newx][newy] == 1e9) {
                    wolf[newx][newy] = wolf[x][y] + 1;
                    q.push({newx, newy});
                }
            } 
        }
    }
}

void bfsHuman() {
    queue<pair<int, int>> q;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j] != 's') {
                human[i][j] = 1e9;
            } else {
                q.push({i, j});
            }
        }
    }
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (auto pi : moves) {
            int newx = pi.first + x;
            int newy = pi.second + y;
            if (newx > 0 && newx <= m && newy > 0 && newy <= n) {
                if (a[newx][newy] != '#' && human[newx][newy] == 1e9) {
                    if (human[x][y] + 1 < wolf[newx][newy]) {
                        human[newx][newy] = human[x][y] + 1;
                        q.push({newx, newy});
                    }
                }
            } 
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    //freopen("TASK.INP", "r", stdin);
    cin >> m >> n >> k;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }
    d.resize(k);
    for (int i = 0; i < k; i++) {
        cin >> d[i];
    }
    prep();
    bfsWolf();
    bfsHuman();
    cout << (human[endPos.first][endPos.second] < wolf[endPos.first][endPos.second] ? human[endPos.first][endPos.second] : -1);
    return 0;
}
