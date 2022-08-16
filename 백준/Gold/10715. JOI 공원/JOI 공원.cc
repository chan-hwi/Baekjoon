#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define INF 1e18
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;

int N, M, C, a, b, d;
ll ans, curSum;
ll dist[100001];
bool visit[100001];
vector<pii> edges[100001];
priority_queue<pli> pq;

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N >> M >> C;
    for (int i = 0; i < M; i++) {
        cin >> a >> b >> d;
        curSum += d;
        edges[a].push_back({ b, d });
        edges[b].push_back({ a, d });
    }
    ans = curSum;

    fill_n(dist, N + 1, INF);
    dist[1] = 0;
    pq.push({ 0, 1 });
    while (!pq.empty()) {
        ll curDist = -pq.top().first;
        int cur = pq.top().second;
        pq.pop();

        if (curDist > dist[cur]) continue;
        for (pii& e : edges[cur]) {
            ll newDist = curDist + e.second;
            if (newDist < dist[e.first]) {
                dist[e.first] = newDist;
                pq.push({ -newDist, e.first });
            } else if (visit[e.first]) curSum -= e.second;
        }

        visit[cur] = true;
        ans = min(ans, curDist * C + curSum);
    }
    cout << ans << '\n';
}