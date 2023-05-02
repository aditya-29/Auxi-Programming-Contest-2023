#include <bits/stdc++.h>

#define el '\n'
#define ll long long
#define ld long double

#define Beevo ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

const int N = 1e5 + 5, INF = 1e9;

struct Node {
    int mn, mx, bst;
};

struct segTree {
    Node tree[N * 4];
    Node neutral = {INF, -INF, 0};

    Node merge(Node u, Node v) {
        Node ret;
        ret.mn = min(u.mn, v.mn);
        ret.mx = max(u.mx, v.mx);
        ret.bst = max({u.bst, v.bst, v.mx - u.mn});

        return ret;
    }

    Node single(int x) {
        return {x, x, 0};
    }
    void build(int x, int l, int r, vector<int> &v) {
        if (l == r) {
            tree[x] = single(v[l]);
            return;
        }

        int m = (l + r) >> 1;

        build(x * 2, l, m, v);
        build(x * 2 + 1, m + 1, r, v);

        tree[x] = merge(tree[x * 2], tree[x * 2 + 1]);
    }

    void set(int x, int l, int r, int i, int v) {
        if (l == r) {
            tree[x] = single(v);
            return;
        }

        int m = (l+r) >> 1;

        if (i <= m)
            set(x * 2, l, m, i, v);
        else
            set(x * 2 + 1, m + 1, r, i, v);
        
        tree[x] = merge(tree[x * 2], tree[x*2+1]);
    }

    Node query(int x, int lx, int rx, int l, int r) {
        if (lx > r || rx < l) {
            return neutral;
        }

        if (lx >= l && rx <= r) {
            return tree[x];
        }

        int m = (lx + rx) >> 1;

        Node u = query(x * 2, lx, m, l, r);
        Node v = query(x * 2 + 1, m+1, rx, l, r);

        return merge(u,v);
    }
} st;

int n;
int sol[N];
vector<int> p[2][7];
pair<int, int> queries[N];
vector<int> m = {0,1,2,3,2,1,0};

void solve(vector<pair<int, int>> &v,  bool t) {
    for (int i = 0, k = 0; i < 7; i++, k++) {
        vector<int> a(n);

    for (int j = 0; j<n;j++) {
        a[j] = v[j].first + m[(k+j)%7] * v[j].second;
    }

    st.build(1, 0, n-1, a);

    for (auto j:p[t][i])
        sol[j] = st.query(1, 0, n-1, queries[j].first, queries[j].second).bst;
    }
}

void testCase() {
    cin >> n;

    vector<pair<int, int>> v(n);

    for (int i=0; i<n; i++) {
        cin >> v[i].first >> v[i].second;
    }

    int q;
    cin >> q;

    int l, r;

    for (int i=0;i<q;i++) {
        cin >> l >> r;
        l--, r--;

        queries[i] = {l,r};

        if (l <= r)
            p[0][(7 - l %7)%7].push_back(i);
        else {
            l = n - l - 1;
            r = n - r - 1;

            queries[i] = {l,r};

            p[1][(7 - l % 7) % 7].push_back(i);
        }
    }

solve(v, 0);
reverse(v.begin(), v.end());

solve(v,1);

for (int i=0; i<q; i++) 
    cout << sol[i] << el;
}

signed main() {
    Beevo

    int T = 1;

    while (T--)
        testCase();

    return 0;
}