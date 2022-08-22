#include <iostream>
using namespace std;

struct Node { int t, o; };

int N, Q, a, b;
int nums[200001];
Node tree[800005];

void init(int i, int j, int n) {
    if (i == j) {
        tree[n] = { nums[i], nums[i] };
        return;
    }
    int m = i + j >> 1;
    init(i, m, n * 2);
    init(m + 1, j, n * 2 + 1);
    tree[n] = { tree[n * 2].t ^ tree[n * 2 + 1].t, 
                tree[n * 2].o ^ tree[n * 2 + 1].o ^ (tree[n * 2 + 1].t * ((m - i) % 2 == 0)) };
}

void update(int i, int j, int n, const int& idx, const int& val) {
    if (i > idx || j < idx) return;
    if (i == j) {
        tree[n] = { val, val };
        return;
    }
    int m = i + j >> 1;
    update(i, m, n * 2, idx, val);
    update(m + 1, j, n * 2 + 1, idx, val);
    tree[n] = { tree[n * 2].t ^ tree[n * 2 + 1].t, 
                tree[n * 2].o ^ tree[n * 2 + 1].o ^ (tree[n * 2 + 1].t * ((m - i) % 2 == 0)) };
}

int findXor(int i, int j, int n, const int& l, const int& r) {
    if (i > r || j < l) return 0;
    if (i >= l && j <= r) {
        if ((i - l + 1) % 2) return tree[n].o;
        return tree[n].t ^ tree[n].o;
    }
    int m = i + j >> 1;
    return findXor(i, m, n * 2, l, r) ^ findXor(m + 1, j, n * 2 + 1, l, r);
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N >> Q;
    for (int i = 1; i <= N; i++) cin >> nums[i];
    init(1, N, 1);

    while (Q--) {
        cin >> a;
        if (a == 1) {
            cin >> a >> b;
            update(1, N, 1, a, b);
        } else {
            cin >> a >> b;
            cout << ((b - a + 1) % 2 ? findXor(1, N, 1, a, b) : 0) << '\n';
        }
    }
}