#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#define INF 987654321
using namespace std;

typedef pair<int, int> pii;

int N, K, u, v, w, halfCnt, ans = INF;
int cnt[200000];
bool visit[200000];
vector<pii> edges[200000];

int initCnt(int i, int p = -1) {
    cnt[i] = 1;
    for (pii e : edges[i]) {
        if (e.first == p || visit[e.first]) continue;
        cnt[i] += initCnt(e.first, i);
    }
    return cnt[i];
}

int getCent(int i, int p = -1) {
    for (pii e : edges[i]) {
        if (e.first == p || visit[e.first]) continue;
        if (halfCnt < cnt[e.first]) return getCent(e.first, i);
    }
    return i;
}

void getCurMin(map<int, int>& minmap, vector<pii>& costs, int i, int p, int cost, int depth = 1) {
    costs.push_back({ cost, depth });
    if (minmap.find(K - cost) != minmap.end()) {
        ans = min(ans, depth + minmap[K - cost]);
    }
    for (pii e : edges[i]) {
        if (e.first == p || visit[e.first]) continue;
        getCurMin(minmap, costs, e.first, i, cost + e.second, depth + 1);
    }
}

void solve(int i) {
    halfCnt = initCnt(i) >> 1;
    int c = getCent(i);
    map<int, int> minmap;
    vector<pii> costs;
    minmap[0] = 0;
    visit[c] = true;
    int j = 0;
    for (pii e : edges[c]) {
        if (visit[e.first]) continue;
        getCurMin(minmap, costs, e.first, c, e.second);
        for (j; j < costs.size(); j++) {
            if (minmap.find(costs[j].first) == minmap.end()) minmap[costs[j].first] = costs[j].second;
            else minmap[costs[j].first] = min(minmap[costs[j].first], costs[j].second);
        }
    }
    for (pii e : edges[c]) if (!visit[e.first]) solve(e.first);
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N >> K;
    for (int i = 1; i < N; i++) {
        cin >> u >> v >> w;
        edges[u].push_back({ v, w });
        edges[v].push_back({ u, w });
    }

    solve(0);
    cout << (ans == INF ? -1 : ans) << '\n';
}