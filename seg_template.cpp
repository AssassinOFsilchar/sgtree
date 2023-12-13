// ABHISHEK RANJAN (GAWD)
// 2112016
#include <bits/stdc++.h>
#define rep(i, a) for (int i = 0; i < a; i++)
#define ll long long
#define inp(n) \
    ll n;      \
    cin >> n;
#define inpv(v)       \
    for (auto &x : v) \
        cin >> x;
#define makevec(vec, n) \
    vector<int> vec(n); \
    fr(i, n) cin >> vec[i];
#define fr(i, n) for (ll i = 0; i < n; ++i)
#define frs(i, k, n) for (ll i = k; i < n; ++i)
#define fA(i, a, n) for (ll i = a; i <= (n); ++i)
#define fD(i, a, n) for (ll i = a; i >= (n); --i)
#define dsort(arr) sort(arr, arr + n, greater<ll>())
#define asort(arr) sort(arr, arr + n)
#define allasort(str) sort(str.begin(), str.end())
#define alldsort(str) sort(str.begin(), str.end(), greater<char>())
#define pb push_back
#define all(_obj) _obj.begin(), _obj.end()
#define F first
#define S second
#define PI 3.141592653589793238
#define pll pair<ll, ll>
#define vll vector<ll>
ll INF = 1e18;
ll max(ll a, ll b) { return ((a > b) ? a : b); }
ll min(ll a, ll b) { return ((a > b) ? b : a); }
using namespace std;
class SGtree
{
    vector<int> seg;

public:
    SGtree(int n)
    {
        seg.resize(4 * n + 1);
    }

    void build(vector<int> &vec, int ind, int l, int r)
    {

        if (l == r)
        {
            seg[ind] = vec[l];
            return;
        }

        int mid = (l + r) >> 1;
        build(vec, 2 * ind + 1, l, mid);
        build(vec, 2 * ind + 2, mid + 1, r);
        seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
    }

    int givin(int l, int r, int low, int high, int ind)
    {
        // l r low high or low high l r .. the case of no overlap
        if (r < low || high < l)
        {
            return INT_MAX;
        }
        // l low high r
        if (l <= low && high <= r)
        {
            return seg[ind];
        }

        // if there is a partial overlap
        int left, right;
        int mid = (low + high) >> 1;
        left = givin(l, r, low, mid, 2 * ind + 1);
        right = givin(l, r, mid + 1, high, 2 * ind + 2);
        return min(left, right);
    }

    void update(int ind, int val, int l, int r, int i, vector<int> &vec)
    {
        if (l == r)
        {
            vec[i] = val;
            seg[ind] = vec[i];
            return;
        }

        int mid = (l + r) >> 1;
        if (i <= mid)
        {
            update(2 * ind + 1, val, l, mid, i, vec);
        }
        else
        {
            update(2 * ind + 2, val, mid + 1, r, i, vec);
        }

        seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<int> vec(n);
    for (int i = 0; i < n; i++)
    {
        cin >> vec[i];
    }
    SGtree seg1(n);
    seg1.build(vec, 0, 0, n - 1);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int l, r;
            cin >> l >> r;
            cout << seg1.givin(l, r, 0, n - 1, 0);
            cout << endl;
        }
        else
        {
            int ind, val;
            cin >> ind >> val;
            seg1.update(0, val, 0, n - 1, ind, vec);
        }
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
        cout << endl;
    }
    return 0;
}