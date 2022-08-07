#include <iostream>
#define MOD 998244353
using namespace std;

typedef long long ll;

int N, M, a, b, c;
ll ans;
ll w[1200005], tree[1200005], lazy[1200005];

void init(int i, int j, int n) {
    lazy[n] = -1;
    if (i == j) {
        w[n] = (ll)i * (N - i + 1) % MOD;
        return;
    }
    int m = i + j >> 1;
    init(i, m, n * 2);
    init(m + 1, j, n * 2 + 1);
    w[n] = (w[n * 2] + w[n * 2 + 1]) % MOD;
}

void lazyProp(int i, int j, int n) {
    if (lazy[n] == -1) return;
    tree[n] = w[n] * lazy[n] % MOD;
    if (i != j) {
        lazy[n * 2] = lazy[n];
        lazy[n * 2 + 1] = lazy[n];
    }
    lazy[n] = -1;
}

void update(int i, int j, int n, int l, int r, int val) {
    lazyProp(i, j, n);
    if (i > r || j < l) return;
    if (i >= l && j <= r) {
        lazy[n] = val;
        lazyProp(i, j, n);
        return;
    }
    int m = i + j >> 1;
    update(i, m, n * 2, l, r, val);
    update(m + 1, j, n * 2 + 1, l, r, val);
    tree[n] = (tree[n * 2] + tree[n * 2 + 1]) % MOD;
}

ll findSum(int i, int j, int n, int l, int r) {
    lazyProp(i, j, n);
    if (i > r || j < l) return 0;
    if (i >= l && j <= r) return tree[n];
    int m = i + j >> 1;
    return (findSum(i, m, n * 2, l, r) + findSum(m + 1, j, n * 2 + 1, l, r)) % MOD;
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N >> M;
    init(1, N, 1);
    for (int i = 1; i <= M; i++) {
        cin >> a >> b >> c;
        update(1, N, 1, a, b, (ll)c * i % MOD);
        ans = (ans + findSum(1, N, 1, 1, N)) % MOD;
    }
    cout << ans << '\n';
}