#include <iostream>
#include <vector>
#define INF 987654321
using namespace std;

int N, a, b, ans = INF;
int nums[10];
bool visit[10], team[10];
vector<int> edges[10];

int dfs(int i, bool t) {
    if (visit[i] || team[i] != t) return 0;
    visit[i] = true;
    int cnt = nums[i];
    for (int j : edges[i]) {
        cnt += dfs(j, t);
    }
    return cnt;
}

void solve(int i = 0) {
    if (i >= N) {
        a = -1, b = -1;
        for (int j = 0; j < N; j++) {
            if (!team[j]) a = j;
            if (team[j]) b = j;
        }
        if (a == -1 || b == -1) return;
        fill_n(visit, N, false);
        a = dfs(a, 0);  b = dfs(b, 1);
        bool pos = true;
        for (int j = 0; j < N; j++) pos &= visit[j];
        if (pos) ans = min(ans, abs(a - b));
        return;
    }
    team[i] = false;    solve(i + 1);
    team[i] = true;     solve(i + 1);
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N;
    for (int i = 0; i < N; i++) cin >> nums[i];
    for (int i = 0; i < N; i++) {
        cin >> a;
        for (int j = 0; j < a; j++) {
            cin >> b;
            edges[i].push_back(b - 1);
        }
    }
    solve();
    cout << (ans == INF ? -1 : ans) << '\n';
}