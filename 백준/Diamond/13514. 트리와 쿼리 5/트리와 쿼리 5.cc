#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define INF 987654321
using namespace std;

typedef pair<int, int> pii;

int N, M, u, v, cd, halfCnt;
int cnt[100001], parent[100001], depth[100001];
int cov[100001][2], tp[17][100001];
bool visit[100001], color[100001];
vector<int> edges[100001];
priority_queue<pii> pq[100001];

void swap(int& a, int& b) { int t = a; a = b; b = t; }

void initDepth(int i, int p = -1) {
    depth[i] = cd++;
    for (int e : edges[i]) {
        if (e == p) continue;
        tp[0][e] = i;
        initDepth(e, i);
    }
    cd--;
}

int initTree(int i, int p = -1) {
    cnt[i] = 1;
    for (int e : edges[i]) {
        if (e == p || visit[e]) continue;
        cnt[i] += initTree(e, i);
    }
    return cnt[i];
}

int getCent(int i, int p = -1) {
    for (int e : edges[i]) {
        if (e == p || visit[e]) continue;
        if (halfCnt < cnt[e]) return getCent(e, i);
    }
    return i;
}

int centDecomp(int i, int p = -1) {
    halfCnt = initTree(i) >> 1;
    int c = getCent(i);

    visit[c] = true;
    parent[c] = p;
    for (int e : edges[c]) {
        if (!visit[e]) centDecomp(e, c);
    }
    return c;
}

int getLca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    int diff = depth[a] - depth[b];
    int i = 0;
    while (diff) {
        if (diff & 1) a = tp[i][a];
        i++;
        diff >>= 1;
    }
    if (a == b) return a;
    for (i = 16; i >= 0; i--) {
        if (tp[i][a] != tp[i][b]) {
            a = tp[i][a];
            b = tp[i][b];
        }
    }
    return tp[0][a];
}

int getDist(int a, int b) {
    int lca = getLca(a, b);
    return depth[a] + depth[b] - depth[lca] * 2;
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N;
    for (int i = 0; i < N - 1; i++) {
        cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    centDecomp(1);
    initDepth(1);
    for (int i = 1; i < 17; i++) {
        for (int j = 1; j <= N; j++) {
            tp[i][j] = tp[i - 1][tp[i - 1][j]];
        }
    }

    cin >> M;
    while (M--) {
        cin >> u >> v;
        if (u == 1) {
            if (!color[v]) {
                int w = v;
                while (w != -1) {
                    pq[w].push({ -getDist(v, w), v });
                    w = parent[w];
                }
            }
            color[v] = !color[v];
        } else {
            int minVal = INF;
            int w = v;
            while (w != -1) {
                while (!pq[w].empty() && !color[pq[w].top().second]) pq[w].pop();
                if (!pq[w].empty()) minVal = min(minVal, -pq[w].top().first + getDist(v, w));
                w = parent[w];
            }
            cout << (minVal >= INF ? -1 : minVal) << '\n';
        }
    }
}