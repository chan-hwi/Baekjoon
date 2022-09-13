#include <iostream>
#define INF 987654321
using namespace std;

int N, num, ans;
int ranks[500001][3], sorted[500001][2];
int tree[2000005];

void init(int i, int j, int n) {
    if (i == j) {
        tree[n] = INF;
        return;
    }
    int m = i + j >> 1;
    tree[n] = INF;
    init(i, m, n * 2);
    init(m + 1, j, n * 2 + 1);
}

void update(int i, int j, int n, const int& idx, const int& val) {
    if (i > idx || j < idx) return;
    if (i == j) {
        tree[n] = val;
        return;
    }
    int m = i + j >> 1;
    update(i, m, n * 2, idx, val);
    update(m + 1, j, n * 2 + 1, idx, val);
    tree[n] = min(tree[n * 2], tree[n * 2 + 1]);
}

int findMin(int i, int j, int n, const int& l, const int& r) {
    if (i > r || j < l) return INF;
    if (i >= l && j <= r) return tree[n];
    int m = i + j >> 1;
    return min(findMin(i, m, n * 2, l, r), findMin(m + 1, j, n * 2 + 1, l, r));
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N;
    for (int i = 0; i < 3; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> num;
            ranks[num][i] = j;
        }
    }
    for (int i = 1; i <= N; i++) {
        sorted[ranks[i][0]][0] = ranks[i][1];
        sorted[ranks[i][0]][1] = ranks[i][2];
    }

    init(1, N, 1);
    for (int i = 1; i <= N; i++) {
        if (sorted[i][1] < findMin(1, N, 1, 1, sorted[i][0])) ans++;
        update(1, N, 1, sorted[i][0], sorted[i][1]);
    }

    cout << ans << '\n';
}