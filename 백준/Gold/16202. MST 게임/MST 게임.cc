#include <iostream>
using namespace std;

struct edge { int a, b; };

int N, M, K, a, b;
int parent[1001], lvl[1001];
bool rem[10000];
edge edges[10000];

void swap(int& a, int& b) { int t = a; a = b; b = t; }

int Find(int u) { return (u == parent[u] ? u : parent[u] = Find(parent[u])); }

void Union(int u, int v) {
    u = Find(u), v = Find(v);
    if (u == v) return;
    if (lvl[u] > lvl[v]) swap(u, v);
    if (lvl[u] == lvl[v]) lvl[v]++;
    parent[u] = v;
}

void initUF() {
    for (int i = 1; i <= N; i++) parent[i] = i;
    fill_n(lvl, N + 1, 0);
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N >> M >> K;

    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        edges[i] = { a, b };
    }

    bool ps = true;
    for (int i = 0; i < K; i++) {
        if (!ps) {
            cout << 0 << ' ';
            continue;
        }

        initUF();
        int cnt = N - 1, score = 0, sm = -1;
        for (int j = 0; j < M; j++) {
            if (rem[j]) continue;
            int &u = edges[j].a, &v = edges[j].b;
            if (Find(u) == Find(v)) continue;
            Union(u, v);
            if (sm == -1) sm = j;
            score += j + 1;
            if ((--cnt) == 0) break;
        }
        if (cnt) {
            ps = false;
            cout << 0 << ' ';
        } else {
            cout << score << ' ';
            rem[sm] = true;
        }
    }
    cout << '\n';
}