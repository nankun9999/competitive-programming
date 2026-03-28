#include <bits/stdc++.h>
using namespace std;
 
int m, n, distA[1005][1005], distMonster[1005][1005];
char trace[1005][1005];
pair<int, int> posA;
char a[1005][1005];
vector<pair<int, int>> boundarySquares;
int dx[] = {0, 1, -1, 0};
int dy[] = {1, 0, 0, -1};
 
void bfsA() {
    distA[posA.first][posA.second] = 1;
    queue<pair<int, int>> q;
    q.push({posA.first, posA.second});
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int newX = dx[i] + x;
            int newY = dy[i] + y;
            if (newX >= 0 && newX < m && newY >= 0 && newY < n) {
                if (a[newX][newY] == '.' && !distA[newX][newY]) {
                    distA[newX][newY] = distA[x][y] + 1;
                    q.push({newX, newY});
                    if (i == 0) {
                        trace[newX][newY] = 'R';
                    } else if (i == 1) {
                        trace[newX][newY] = 'D';
                    } else if (i == 2) {
                        trace[newX][newY] = 'U';
                    } else {
                        trace[newX][newY] = 'L';
                    }
                }
            }
        }
    }
}
 
void bfsMonster() {
    queue<pair<int, int>> q;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] == 'M') {
                q.push({i, j});
                distMonster[i][j] = 1;
            }
        }
    }
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int newX = dx[i] + x;
            int newY = dy[i] + y;
            if (newX >= 0 && newX < m && newY >= 0 && newY < n) {
                if (a[newX][newY] != '#' && !distMonster[newX][newY]) {
                    distMonster[newX][newY] = distMonster[x][y] + 1;
                    q.push({newX, newY});
                }
            }
        }
    }
}
 
void process(int x, int y) {
    cout << "YES" << "\n";
    vector<char> res;
    while (x != posA.first || y != posA.second) {
        res.push_back(trace[x][y]);
        if (trace[x][y] == 'L') {
            y++;
        } else if (trace[x][y] == 'R') {
            y--;
        } else if (trace[x][y] == 'D') {
            x--;
        } else if (trace[x][y] == 'U') {
            x++;
        }
    }
    cout << res.size() << "\n";
    for (int i = res.size() - 1; i >= 0; i--) {
        cout << res[i];
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    //freopen("TASK.INP", "r", stdin);
    cin >> m >> n;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
            if (a[i][j] != '#' && (i == 0 || i == m - 1 || j == 0 || j == n - 1)) {
                boundarySquares.push_back({i, j});
            }
            if (a[i][j] == 'A') {
                posA = {i, j};
            }
        }
    }
    bfsA();
    bfsMonster();
    for (auto p : boundarySquares) {
        if (distA[p.first][p.second] && (distA[p.first][p.second] < distMonster[p.first][p.second] || !distMonster[p.first][p.second])) {
            process(p.first, p.second);
            return 0;
        }
    }
    cout << "NO" << "\n";
    return 0;
}
