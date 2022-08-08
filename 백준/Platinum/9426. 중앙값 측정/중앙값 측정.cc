#include <iostream>
#include <queue>
#define MAX 65535
using namespace std;

int N, K, num;
long long ans;
int tree[MAX << 2];
queue<int> q;

void toggleVal(int i, int j, int n, int idx, int val) {
    if (i == j) {
        tree[n] += val;
        return;
    }
    int m = i + j >> 1;
    if (idx <= m) toggleVal(i, m, n * 2, idx, val);
    else toggleVal(m + 1, j, n * 2 + 1, idx, val);
    tree[n] = tree[n * 2] + tree[n * 2 + 1];
}

int findKth(int i, int j, int n, int k) {
    if (i == j) return i;
    int m = i + j >> 1;
    if (k <= tree[n * 2]) return findKth(i, m, n * 2, k);
    return findKth(m + 1, j, n * 2 + 1, k - tree[n * 2]);
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> num;
        toggleVal(0, MAX, 1, num, 1);
        q.push(num);
        if (q.size() >= K) {
            ans += findKth(0, MAX, 1, (K + 1) >> 1);
            toggleVal(0, MAX, 1, q.front(), -1);
            q.pop();
        }
    }
    cout << ans << '\n';
}