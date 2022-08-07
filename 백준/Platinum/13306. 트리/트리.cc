#include <iostream>
using namespace std;

int N, Q, M;
int treeParent[200001], ufParent[200001], lvl[200001];
int query[400000][3];
bool ans[200000];

void swap(int& u, int& v) { int t = u; u = v; v = t; }

int Find(int u) {
    return (u == ufParent[u] ? u : ufParent[u] = Find(ufParent[u]));
}

void Union(int u, int v) {
    u = Find(u), v = Find(v);
    if (u == v) return;
    if (lvl[u] > lvl[v]) swap(u, v);
    if (lvl[u] == lvl[v]) lvl[v]++;
    ufParent[u] = v;
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N >> Q;
    M = Q + N - 1;
    for (int i = 1; i <= N; i++) ufParent[i] = i;
    for (int i = 2; i <= N; i++) cin >> treeParent[i];
    for (int i = 0; i < M; i++) {
        cin >> query[i][0];
        if (query[i][0]) cin >> query[i][1] >> query[i][2];
        else cin >> query[i][1];
    }

    int cnt = 0;
    for (int i = M - 1; i >= 0; i--) {
        if (query[i][0]) ans[cnt++] = Find(query[i][1]) == Find(query[i][2]);
        else Union(treeParent[query[i][1]], query[i][1]);
    }
    for (int i = cnt - 1; i >= 0; i--) cout << (ans[i] ? "YES" : "NO") << '\n';
}