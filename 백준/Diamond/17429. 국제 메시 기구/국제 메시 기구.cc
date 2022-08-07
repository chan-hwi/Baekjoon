#include <iostream>
#include <vector>
using namespace std;

int N, M, a, b, c, ci, cci, ccd;
int chainIdx[500001], chainOrd[500001], chainDepth[500001], parent[500001], cnt[500001];
int covRange[500001][2];
unsigned tree[2000005];
unsigned lazy[2000005][2];
vector<int> edges[500001], chain[500001];

void swap(int& u, int& v) { int t = a; a = b; b = t; }

void segTreeInit(int i, int j, int n) {
    lazy[n][0] = 1;
    if (i == j) return;
    int m = i + j >> 1;
    segTreeInit(i, m, n * 2);
    segTreeInit(m + 1, j, n * 2 + 1);
}

void lazyProp(int i, int j, int n) {
    tree[n] = tree[n] * lazy[n][0] + lazy[n][1] * (j - i + 1);
    if (i != j) {
        for (int ch : { n * 2, n * 2 + 1 }) {
            lazy[ch][0] *= lazy[n][0];
            lazy[ch][1] *= lazy[n][0];
            lazy[ch][1] += lazy[n][1];
        }
    }
    lazy[n][0] = 1;
    lazy[n][1] = 0;
}

unsigned findSum(int i, int j, int n, int l, int r) {
    lazyProp(i, j, n);
    if (i > r || j < l) return 0;
    if (i >= l && j <= r) return tree[n];
    int m = i + j >> 1;
    return findSum(i, m, n * 2, l, r) + findSum(m + 1, j, n * 2 + 1, l, r);
}

void update(int i, int j, int n, int l, int r, unsigned val, bool s) {
    lazyProp(i, j, n);
    if (i > r || j < l) return;
    if (i >= l && j <= r) {
        lazy[n][s] = val;
        lazyProp(i, j, n);
        return;
    }
    int m = i + j >> 1;
    update(i, m, n * 2, l, r, val, s);
    update(m + 1, j, n * 2 + 1, l, r, val, s);
    tree[n] = tree[n * 2] + tree[n * 2 + 1];
}

int dfsInit(int i, int p = -1) {
    cnt[i] = 1;
    parent[i] = p;
    for (int e : edges[i]) {
        if (e == p) continue;
        cnt[i] += dfsInit(e, i);
    }
    return cnt[i];
}

void HLD(int i, int p = -1) {
    chainIdx[i] = cci;
    chainDepth[i] = ccd;
    chainOrd[i] = chain[cci].size();
    chain[cci].push_back(i);
    covRange[i][0] = ++ci;
    int maxVal = -1, maxIdx = -1;
    for (int e : edges[i]) {
        if (e == p) continue;
        if (maxVal < cnt[e]) {
            maxVal = cnt[e];
            maxIdx = e;
        }
    }
    if (maxIdx == -1) {
        covRange[i][1] = ci;
        return;
    }
    HLD(maxIdx, i);
    ccd++;
    for (int e : edges[i]) {
        if (e == p || e == maxIdx) continue;
        cci++;
        HLD(e, i);
    }
    covRange[i][1] = ci;
    ccd--;
}

void updatePath(bool s) {
    while (chainIdx[a] != chainIdx[b]) {
        if (chainDepth[a] < chainDepth[b]) swap(a, b);
        int an = chain[chainIdx[a]][0];
        update(1, N, 1, covRange[an][0], covRange[a][0], c, s);
        a = parent[an];
    }
    if (chainOrd[a] > chainOrd[b]) swap(a, b);
    update(1, N, 1, covRange[a][0], covRange[b][0], c, s);
}

unsigned findPathSum() {
    unsigned sum = 0;
    while (chainIdx[a] != chainIdx[b]) {
        if (chainDepth[a] < chainDepth[b]) swap(a, b);
        int an = chain[chainIdx[a]][0];
        sum += findSum(1, N, 1, covRange[an][0], covRange[a][0]);
        a = parent[an];
    }
    if (chainOrd[a] > chainOrd[b]) swap(a, b);
    sum += findSum(1, N, 1, covRange[a][0], covRange[b][0]);
    return sum;
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N >> M;
    segTreeInit(1, N, 1);
    for (int i = 1; i < N; i++) {
        cin >> a >> b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    dfsInit(1);
    HLD(1);
    for (int i = 0; i < M; i++) {
        cin >> a;
        if (a == 1 || a == 3) {
            cin >> b >> c;
            update(1, N, 1, covRange[b][0], covRange[b][1], c, a == 1);
        } else if (a == 2 || a == 4) {
            bool mode = a == 2;
            cin >> a >> b >> c;
            updatePath(mode);
        } else if (a == 5) {
            cin >> a;
            cout << findSum(1, N, 1, covRange[a][0], covRange[a][1]) << '\n';
        } else {
            cin >> a >> b;
            cout << findPathSum() << '\n';
        }
    }
}