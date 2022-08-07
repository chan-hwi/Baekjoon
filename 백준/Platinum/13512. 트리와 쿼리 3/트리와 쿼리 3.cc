#include <iostream>
#include <vector>
using namespace std;

int N, M, u, v, ci, cci, ccd;
int cnt[100001], parent[100001], indices[100001], invIdx[100001];
int chainGrp[100001], chainDepth[100001], chainOrd[100001];
vector<int> edges[100001], chain[100001];
bool tree[400005];

void swap(int& a, int& b) { int t = a; a = b; b = t; }

void initTree(int i = 1, int p = -1) {
    parent[i] = p;
    cnt[i] = 1;
    for (int e : edges[i]) {
        if (e == p) continue;
        initTree(e, i);
        cnt[i] += cnt[e];
    }
}

void HLD(int i = 1, int p = -1) {
    indices[i] = ++ci;
    invIdx[ci] = i;
    chainGrp[i] = cci;
    chainDepth[i] = ccd;
    chainOrd[i] = chain[cci].size();
    chain[cci].push_back(i);

    int maxVal = -1, maxIdx = -1;
    for (int e : edges[i]) {
        if (e == p) continue;
        if (maxVal < cnt[e]) {
            maxVal = cnt[e];
            maxIdx = e;
        }
    }
    if (maxIdx != -1) HLD(maxIdx, i);

    ccd++;
    for (int e : edges[i]) {
        if (e == p || e == maxIdx) continue;
        cci++;
        HLD(e, i);
    }
    ccd--;
}

void update(int i, int j, int n, int idx) {
    if (i > idx || j < idx) return;
    if (i == j) {
        tree[n] = !tree[n];
        return;
    }
    int m = i + j >> 1;
    update(i, m, n * 2, idx);
    update(m + 1, j, n * 2 + 1, idx);
    tree[n] = tree[n * 2] || tree[n * 2 + 1];
}

int getIdx(int i, int j, int n, int l, int r, bool s) {
    if (i > r || j < l || !tree[n]) return -1;
    int m = i + j >> 1;
    if (i >= l && j <= r) {
        if (i == j) return invIdx[i];
        if (s) return (tree[n * 2] ? getIdx(i, m, n * 2, l, r, s) : getIdx(m + 1, j, n * 2 + 1, l, r, s));
        else return (tree[n * 2 + 1] ? getIdx(m + 1, j, n * 2 + 1, l, r, s) : getIdx(i, m, n * 2, l, r, s));
    }
    int left = getIdx(i, m, n * 2, l, r, s);
    int right = getIdx(m + 1, j, n * 2 + 1, l, r, s);
    if (s) return (left == -1 ? right : left);
    else return (right == -1 ? left : right);
}

int findClosestNode(int a, int b) {
    int ret = -1;
    while (chainGrp[a] != chainGrp[b]) {
        if (chainDepth[a] > chainDepth[b]) {
            int cur = getIdx(1, N, 1, indices[chain[chainGrp[a]][0]], indices[a], false);
            if (cur != -1) return cur;
            a = parent[chain[chainGrp[a]][0]];
        } else {
            int cur = getIdx(1, N, 1, indices[chain[chainGrp[b]][0]], indices[b], true);
            if (cur != -1) ret = cur;
            b = parent[chain[chainGrp[b]][0]];
        }
    }
    bool s = true;
    if (chainOrd[a] > chainOrd[b]) {
        s = false;
        swap(a, b);
    }
    int cur = getIdx(1, N, 1, indices[a], indices[b], s);
    if (cur != -1) return cur;
    return ret;
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N;
    for (int i = 0; i < N - 1; i++) {
        cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    initTree();
    HLD();

    cin >> M;
    while (M--) {
        cin >> u >> v;
        if (u == 1) update(1, N, 1, indices[v]);
        else cout << findClosestNode(1, v) << '\n';
    }
}