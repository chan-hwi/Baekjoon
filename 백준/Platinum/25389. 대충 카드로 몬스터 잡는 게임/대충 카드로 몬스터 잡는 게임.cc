#include <iostream>
using namespace std;

int N, K, M;
int nums[500001], idx[500001], tree[2000005], lazy[2000005];

void lazyProp(int i, int j, int n) {
    if (!lazy[n]) return;
    tree[n] += lazy[n];
    if (i != j) {
        lazy[n * 2] += lazy[n];
        lazy[n * 2 + 1] += lazy[n];
    }
    lazy[n] = 0;
}

void incArea(int i, int j, int n, int l, int r) {
    lazyProp(i, j, n);
    if (i > r || j < l) return;
    if (i >= l && j <= r) {
        tree[n]++;
        if (i != j) {
            lazy[n * 2]++;
            lazy[n * 2 + 1]++;
        }
        return;
    }
    int m = i + j >> 1;
    incArea(i, m, n * 2, l, r);
    incArea(m + 1, j, n * 2 + 1, l, r);
    tree[n] = max(tree[n * 2], tree[n * 2 + 1]);
}

void setIdx(int i, int j, int n, int idx, int val) {
    lazyProp(i, j, n);
    if (i > idx || j < idx) return;
    if (i == j) {
        tree[n] = val;
        return;
    }
    int m = i + j >> 1;
    setIdx(i, m, n * 2, idx, val);
    setIdx(m + 1, j, n * 2 + 1, idx, val);
    tree[n] = max(tree[n * 2], tree[n * 2 + 1]);
}

int findMax(int i, int j, int n, int l, int r) {
    lazyProp(i, j, n);
    if (i > r || j < l) return 0;
    if (i >= l && j <= r) return tree[n];
    int m = i + j >> 1;
    return max(findMax(i, m, n * 2, l, r), findMax(m + 1, j, n * 2 + 1, l, r));
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N >> K;
    M = (K + 1) / 2;
    for (int i = 1; i <= N; i++) cin >> nums[i];
    for (int i = 1; i <= N; i++) {
        if (nums[i]) {
            incArea(0, N, 1, idx[nums[i]], i - 1);
            idx[nums[i]] = i;
        }
        if (i >= M) setIdx(0, N, 1, i, findMax(0, N, 1, 0, i - M));
    }
    cout << findMax(0, N, 1, 0, N) << '\n';
}