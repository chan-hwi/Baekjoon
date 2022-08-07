#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct state { int i; bool isOdd; };

int N, M, u, v;
int cnt[2];
long long ans;
bool visit[50001][2];
vector<int> edges[50001];

void bfs() {
    queue<state> q;
    visit[1][0] = true;
    q.push({ 1, false });
    while (!q.empty()) {
        state s = q.front();
        q.pop();

        for (int e : edges[s.i]) {
            if (visit[e][!s.isOdd]) continue;
            visit[e][!s.isOdd] = true;
            q.push({ e, !s.isOdd });
        }
    }
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    bfs();
    for (int i = 1; i <= N; i++) {
        if (visit[i][0] && visit[i][1]) continue;
        cnt[visit[i][1]]++;
    }

    for (int i = 1; i <= N; i++) {
        if (visit[i][0] && visit[i][1]) continue;
        ans += cnt[visit[i][0]];
        cnt[visit[i][1]]--;
    }
    ans <<= 1;
    cout << ans << '\n';
}