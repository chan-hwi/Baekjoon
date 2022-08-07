#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int, int> pii;

int N, M, u, v, w, ci, cci, ccd;
int edgeIdx[100001], vertexIdx[100001], edgeCost[100000], cnt[100001], parent[100001], indices[100001], invIdx[100001];
int chainOrd[100001], chainDepth[100001], chainGrp[100001];
int tree[400005];
vector<int> chain[100001];
vector<pii> edges[100001];

void swap(int& a, int& b) { int t = a; a = b; b = t; }

void initTree(int i = 1, int p = -1) {
    cnt[i] = 1;
    parent[i] = p;
    for (pii& e : edges[i]) {
        if (e.first == p) continue;
        vertexIdx[e.second] = e.first;
        edgeIdx[e.first] = e.second;
        initTree(e.first, i);
        cnt[i] += cnt[e.first];
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
    for (pii& e : edges[i]) {
        if (e.first == p) continue;
        if (maxVal < cnt[e.first]) {
            maxVal = cnt[e.first];
            maxIdx = e.first;
        }
    }
    if (maxIdx != -1) HLD(maxIdx, i);
    
    ccd++;
    for (pii& e : edges[i]) {
        if (e.first == p || e.first == maxIdx) continue;
        cci++;
        HLD(e.first, i);
    }
    ccd--;
}

void initSegtree(int i, int j, int n) {
    if (i == j) {
        tree[n] = edgeCost[edgeIdx[invIdx[i]]];
        return;
    }
    int m = i + j >> 1;
    initSegtree(i, m, n * 2);
    initSegtree(m + 1, j, n * 2 + 1);
    tree[n] = max(tree[n * 2], tree[n * 2 + 1]);
}

void update(int i, int j, int n, int idx, int val) {
    if (i > idx || j < idx) return;
    if (i == j) {
        tree[n] = val;
        return;
    }
    int m = i + j >> 1;
    update(i, m, n * 2, idx, val);
    update(m + 1, j, n * 2 + 1, idx, val);
    tree[n] = max(tree[n * 2], tree[n * 2 + 1]);
}

int findMax(int i, int j, int n, int l, int r) {
    if (i > r || j < l) return 0;
    if (i >= l && j <= r) return tree[n];
    int m = i + j >> 1;
    return max(findMax(i, m, n * 2, l, r), findMax(m + 1, j, n * 2 + 1, l, r));
}

int findPathMax(int a, int b) {
    int maxVal = 0;
    while (chainGrp[a] != chainGrp[b]) {
        if (chainDepth[a] < chainDepth[b]) swap(a, b);
        maxVal = max(maxVal, findMax(1, N, 1, indices[chain[chainGrp[a]][0]], indices[a]));
        a = parent[chain[chainGrp[a]][0]];
    }
    if (chainOrd[a] == chainOrd[b]) return maxVal;
    if (chainOrd[a] > chainOrd[b]) swap(a, b);
    return maxVal = max(maxVal, findMax(1, N, 1, indices[a] + 1, indices[b]));
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N;
    for (int i = 1; i < N; i++) {
        cin >> u >> v >> w;
        edges[u].push_back({ v, i });
        edges[v].push_back({ u, i });
        edgeCost[i] = w;
    }
    initTree();
    HLD();
    initSegtree(1, N, 1);
    
    cin >> M;
    while (M--) {
        cin >> u >> v >> w;
        if (u == 1) update(1, N, 1, indices[vertexIdx[v]], w);
        else cout << findPathMax(v, w) << '\n';
    }
}