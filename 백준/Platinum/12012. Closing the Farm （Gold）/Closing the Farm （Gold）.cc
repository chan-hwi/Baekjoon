#include <iostream>
#include <vector>
using namespace std;

int N, M, a, b;
int pr[200001], lvl[200001], cnt[200001];
int qrs[200000];
bool ans[200000];
vector<int> edges[200001];

void swap(int& u, int& v) { int t = u; u = v; v = t; }
int Find(int u) { return u == pr[u] ? u : pr[u] = Find(pr[u]); }
void Union(int u, int v) {
    u = Find(u), v = Find(v);
    if (u == v) return;
    if (lvl[u] > lvl[v]) swap(u, v);
    else if (lvl[u] == lvl[v]) lvl[v]++;
    pr[u] = v;
    cnt[v] += cnt[u];
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N >> M;
    fill_n(pr, N + 1, -1);
    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    for (int i = 0; i < N; i++) cin >> qrs[i];
    for (int i = N - 1; i >= 0; i--) {
        int cur = qrs[i];
        pr[cur] = cur;
        cnt[cur] = 1;
        for (int e : edges[cur]) {
            if (pr[e] != -1) Union(cur, e);
        }
        ans[i] = (cnt[Find(cur)] == N - i);
    }
    for (int i = 0; i < N; i++) cout << (ans[i] ? "YES" : "NO") << '\n';
}