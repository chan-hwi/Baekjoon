#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#define INF 987654321
using namespace std;

typedef pair<int, int> pii;

int N, M, a, b, c;
int dist[1001], pr[1001];
vector<pii> ans;
vector<pii> edges[1001];
priority_queue<pii> pq;

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N >> M;
    while (M--) {
        cin >> a >> b >> c;
        edges[a].push_back({ b, c });
        edges[b].push_back({ a, c });
    }
    pq.push({ 0, 1 });
    fill_n(dist, N + 1, INF);
    dist[1] = 0;

    while (!pq.empty()) {
        pii cur = pq.top();
        int curDist = -cur.first;
        int curNode = cur.second;
        pq.pop();

        if (dist[curNode] < curDist) continue;
        if (curNode != 1) ans.push_back({ curNode, pr[curNode] });
        for (pii e : edges[curNode]) {
            int newDist = curDist + e.second;
            if (newDist < dist[e.first]) {
                dist[e.first] = newDist;
                pq.push({ -newDist, e.first });
                pr[e.first] = curNode;
            }
        }
    }

    cout << ans.size() << '\n';
    for (pii edge : ans) {
        cout << edge.first << ' ' << edge.second << '\n';
    }
}