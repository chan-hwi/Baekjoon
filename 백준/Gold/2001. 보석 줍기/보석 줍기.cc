#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct edge { int v, w; };

int N, M, K, u, v, w, ans;
int jw[14], bm[101];
int dp[101][1 << 14];
bool route[15][101][101];
vector<edge> edges[101];

void bfs(int v, int w) {
    queue<int> q;
    vector<bool> visit(N + 1, false);
    visit[v] = true;
    q.push(v);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        
        for (auto &e : edges[cur]) {
            if (visit[e.v] || w > e.w) continue;
            visit[e.v] = true;
            q.push(e.v);
            route[w][v][e.v] = true;
        }
    }
}

int solve(int i, int cbm, int cnt) {
    int &ret = dp[i][cbm];
    if (ret != -1) return ret;

    ret = (i == 1 || route[cnt][i][1] ? cnt : 0);
    for (int idx = 0; idx < K; idx++) {
        int j = jw[idx];
        if (!route[cnt][i][j] || (cbm & bm[j])) continue;
        ret = max(ret, solve(j, cbm | bm[j], cnt + 1));
    }
    return ret;
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N >> M >> K;
    fill(&dp[0][0], &dp[N][1 << K], -1);
    for (int i = 0; i < K; i++) {
        cin >> jw[i];
        bm[jw[i]] = 1 << i;
    }
    for (int i = 0; i < M; i++) {
        cin >> u >> v >> w;
        edges[u].push_back({ v, w });
        edges[v].push_back({ u, w });
    }

    for (int w = 0; w <= K; w++) for (int v = 0; v < K; v++) bfs(jw[v], w);
    for (int i = 0; i < K; i++) {
        ans = max(ans, solve(jw[i], bm[jw[i]], 1));
    }
    cout << ans << '\n';
}