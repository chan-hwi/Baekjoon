#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int N, S, l, r;
int x[1000000], h[1000000];
int sorted[1000000];
bool ans[1000000];
queue<int> q;

bool cmp(int i, int j) {
    return x[i] < x[j];
}

int getLeft(int cx) {
    int a = -1, b = N;
    while (a + 1 != b) {
        int m = a + b >> 1;
        if (cx <= x[m]) b = m;
        else a = m;
    }
    return b;
}

int getRight(int cx) {
    int a = -1, b = N;
    while (a + 1 != b) {
        int m = a + b >> 1;
        if (cx >= x[m]) a = m;
        else b = m;
    }
    return a;
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N >> S;
    l = r = S - 1;
    q.push(S - 1);
    for (int i = 0; i < N; i++) cin >> x[i];
    for (int i = 0; i < N; i++) cin >> h[i];
    for (int i = 0; i < N; i++) sorted[i] = i;
    sort(sorted, sorted + N, cmp);

    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        ans[cur] = true;
        int cl = getLeft(x[cur] - h[cur]), cr = getRight(x[cur] + h[cur]);
        while (l && l > cl) q.push(--l);
        while (r < N - 1 && r < cr) q.push(++r);
    }

    for (int i = 0; i < N; i++) if (ans[i]) cout << i + 1 << ' ';
    cout << '\n';
}