#include <iostream>
using namespace std;

int N, M, a, b;
int parent[1001], lvl[1001], enemy[1001];
bool edges[1001][1001];

void swap(int &u, int& v) { int t = u; u = v; v = t; }

int Find(int u) {
    if (u == parent[u]) return u;
    return parent[u] = Find(parent[u]);
}

void Union(int u, int v) {
    u = Find(u), v = Find(v);
    if (u == v) return;

    if (lvl[u] > lvl[v]) swap(u, v);
    else if (lvl[u] == lvl[v]) lvl[v]++;
    parent[u] = v;
}

bool makeFriend(int u, int v) {
    u = Find(u), v = Find(v);
    int eu = (enemy[u] ? Find(enemy[u]) : 0);
    int ev = (enemy[v] ? Find(enemy[v]) : 0);
    if (eu && eu == v || ev && ev == u) return false;

    Union(u, v);
    enemy[Find(u)] = max(eu, ev);
    if (eu && ev) Union(eu, ev);
    if (eu || ev) enemy[Find(max(eu, ev))] = Find(u);
    return true;
}

bool makeEnemy(int u, int v) {
    u = Find(u), v = Find(v);
    int eu = (enemy[u] ? Find(enemy[u]) : 0);
    int ev = (enemy[v] ? Find(enemy[v]) : 0);
    if (u == v || eu && ev && eu == ev) return false;

    if (ev) Union(u, ev);
    if (eu) Union(v, eu);
    enemy[Find(u)] = Find(v);
    enemy[Find(v)] = Find(u);
    return true;
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N >> M;
    for (int i = 1; i <= N; i++) parent[i] = i;
    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        if (a > b) swap(a, b);
        edges[a][b] = true;
    }

    for (int i = 1; i < N; i++) {
        for (int j = i + 1; j <= N; j++) {
            bool ret = edges[i][j] ? makeFriend(i, j) : makeEnemy(i, j);
            if (!ret) {
                cout << "NE" << '\n';
                return 0;
            }
        }
    }
    cout << "DA" << '\n';
}