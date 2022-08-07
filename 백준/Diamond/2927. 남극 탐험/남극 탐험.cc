#include <iostream>
#include <vector>
#include <map>
using namespace std;

int N, M, cci, ccd, ci = 1;
int nums[30001], tree[30001], treeIdx[30001], treeParent[30001];
int ufParent[30001], ufRank[30001];
int cnt[30001], chainGrp[30001], chainOrd[30001], chainDepth[30001];
int qr[300000][3];
vector<int> edges[30001], chain[30001];
map<string, int> StrtoIdx;
string str;

void swap(int& a, int& b) { int t = a; a = b; b = t; }

void initParent() {
    for (int i = 1; i <= N; i++) ufParent[i] = i;
}

int Find(int u) {
    if (u == ufParent[u]) return u;
    return ufParent[u] = Find(ufParent[u]);
}

bool Union(int u, int v) {
    u = Find(u), v = Find(v);
    if (u == v) return false;;
    if (ufRank[u] > ufRank[v]) swap(u, v);
    else if (ufRank[u] == ufRank[v]) ufRank[v]++;
    ufParent[u] = v;
    return true;
}


int initTree(int i, int p = -1) {
    cnt[i] = 1;
    treeParent[i] = p;
    for (int e : edges[i]) {
        if (e == p) continue;
        cnt[i] += initTree(e, i);
    }
    return cnt[i];
}

void HLD(int i, int p = -1) {
    treeIdx[i] = ci++;
    chainGrp[i] = cci;
    chainOrd[i] = chain[cci].size();
    chainDepth[i] = ccd;
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

void update(int i, int diff) {
    while (i <= N) {
        tree[i] += diff;
        i += (i & -i);
    }
}

int findSum(int i) {
    int sum = 0;
    while (i) {
        sum += tree[i];
        i -= (i & -i);
    }
    return sum;
}

int getPathSum(int a, int b) {
    int sum = 0;
    while (chainGrp[a] != chainGrp[b]) {
        if (chainDepth[a] < chainDepth[b]) swap(a, b);
        sum += findSum(treeIdx[a]) - findSum(treeIdx[chain[chainGrp[a]][0]] - 1);
        a = treeParent[chain[chainGrp[a]][0]];
    }
    if (chainOrd[a] > chainOrd[b]) swap(a, b);
    sum += findSum(treeIdx[b]) - findSum(treeIdx[a] - 1);
    return sum;
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    StrtoIdx["bridge"] = 0, StrtoIdx["penguins"] = 1, StrtoIdx["excursion"] = 2;
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> nums[i];
    initParent();
    cin >> M;
    for (int i = 0; i < M; i++) {
        cin >> str >> qr[i][1] >> qr[i][2];
        qr[i][0] = StrtoIdx[str];
        if (!qr[i][0] && Union(qr[i][1], qr[i][2])) {
            edges[qr[i][1]].push_back(qr[i][2]);
            edges[qr[i][2]].push_back(qr[i][1]);
        }
    }
    initParent();

    for (int i = 1; i <= N; i++) {
        if (!cnt[i]) {
            initTree(i);
            HLD(i);
        }
        update(treeIdx[i], nums[i]);
    }

    for (int i = 0; i < M; i++) {
        if (qr[i][0] == 0) {
            if (Union(qr[i][1], qr[i][2])) cout << "yes" << '\n';
            else cout << "no" << '\n';
        } else if (qr[i][0] == 1) {
            int diff = qr[i][2] - nums[qr[i][1]];
            nums[qr[i][1]] = qr[i][2];
            update(treeIdx[qr[i][1]], diff);
        } else {
            if (Find(qr[i][1]) != Find(qr[i][2])) cout << "impossible" << '\n';
            else {
                cout << getPathSum(qr[i][1], qr[i][2]) << '\n';
            }
        }
    }
}