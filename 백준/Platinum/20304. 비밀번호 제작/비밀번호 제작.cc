#include <iostream>
#include <cmath>
#include <queue>
using namespace std;

int N, M, K, num, ans;
int visit[1000001];
queue<int> q;

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N >> M;
    K = log2(N);
    fill_n(visit, N + 1, -1);
    for (int i = 0; i < M; i++) {
        cin >> num;
        visit[num] = 0;
        q.push(num);
    }

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        for (int d = K; d >= 0; d--) {
            int newVal = cur ^ (1 << d);
            if (newVal < 0 || newVal > N) continue;
            if (visit[newVal] != -1) continue;
            visit[newVal] = visit[cur] + 1;
            ans = max(ans, visit[newVal]);
            q.push(newVal);
        }
    }
    cout << ans << '\n';
}