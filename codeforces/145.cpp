#include <bits/stdc++.h>

using namespace std;

void setup() {
#ifndef ONLINE_JUDGE
    freopen("TASK.INP", "r", stdin);
    freopen("TASK.OUT", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
}

int n, m;
string s;

struct SegmentTree {
    struct NODE {
        int Count4, Count7, BestInc, BestDec;
    } seg[4000005];

    bool lazy[4000005];

    inline NODE Merge(NODE left, NODE right) {
        NODE res;
        res.Count4 = left.Count4 + right.Count4;
        res.Count7 = left.Count7 + right.Count7;
        res.BestInc = max(left.Count4 + right.BestInc, left.BestInc + right.Count7);
        res.BestDec = max(left.Count7 + right.BestDec, left.BestDec + right.Count4);
        return res;
    }

    inline void Flip(NODE &a) {
        swap(a.Count4, a.Count7);
        swap(a.BestDec, a.BestInc);
    }

    inline void Push(int id) {
        if (lazy[id]) {
            Flip(seg[id * 2]);
            Flip(seg[id * 2 + 1]);
            lazy[id * 2] ^= 1;
            lazy[id * 2 + 1] ^= 1;
            lazy[id] = false;
        }
    }

    inline void Build(int id, int l, int r) {
        if (l == r) {
            if (s[l - 1] == '4') {
                seg[id] = {1, 0, 1, 1};
            } else {
                seg[id] = {0, 1, 1, 1};
            }
            return;
        }
        int mid = (l + r) / 2;
        Build(id * 2, l, mid);
        Build(id * 2 + 1, mid + 1, r);
        seg[id] = Merge(seg[id * 2], seg[id * 2 + 1]);
    }

    inline void Update(int id, int l, int r, int u, int v) {
        if (l > v || r < u) {
            return;
        }
        if (l >= u && r <= v) {
            Flip(seg[id]);
            lazy[id] ^= 1;
            return;
        }
        Push(id);
        int mid = (l + r) / 2;
        Update(id * 2, l, mid, u, v);
        Update(id * 2 + 1, mid + 1, r, u, v);
        seg[id] = Merge(seg[id * 2], seg[id * 2 + 1]);
    }
} st;

int main() {
    setup();
    
    cin >> n >> m >> s;
    st.Build(1, 1, n);
    while (m--) {
        string type;
        cin >> type;
        if (type == "count") {
            cout << st.seg[1].BestInc << "\n";
        } else {
            int l, r;
            cin >> l >> r;
            st.Update(1, 1, n, l, r);
        }
    }

    return 0;
}
