#include <iostream>
#include <vector>
using namespace std;

int N, M, K, u, v;
bool visit[100001];
vector<int> edges[2][100001];

void dfs(int i, const bool& b, int& cnt) {
    if (visit[i]) return;
    visit[i] = true;
    cnt++;
    for (int e : edges[b][i]) dfs(e, b, cnt);
}

int solve(int i, const bool& b) {
    fill_n(visit, N + 1, false);
    int ret = 0;
    dfs(i, b, ret);
    return ret;
}


int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N >> M >> K;
    for (int i = 0; i < M; i++) {
        cin >> u >> v;
        edges[0][u].push_back(v);
        edges[1][v].push_back(u);
    }

    int a = solve(K, 0), b = solve(K, 1);
    cout << b << ' ' << N - a + 1 << '\n';   
}