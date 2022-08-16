#include <iostream>
#include <vector>
using namespace std;

int T, N;
vector<int> ans[101];
struct triple { int a, b, c; };

void solve(int N) {
    if (!ans[N].empty()) return;
    vector<int> cnt(N + 1, 0);
    vector<bool> act, rem(N + 1, false);
    vector<triple> trps;
    vector<vector<int>> edges(N + 1);

    int M = 0;
    for (int i = 1; i <= N - 2; i++) {
        for (int j = i + 1; j <= N - 1; j++) {
            int k = i ^ j;
            if (k > j && k <= N) {
                for (int n : { i, j, k }) {
                    cnt[n]++;
                    edges[n].push_back(M);
                }
                M++;
                trps.push_back({ i, j, k });
            }
        }
    }
    act.resize(M, true);
    int rcnt = M;

    while (rcnt) {
        int maxVal = 0, maxIdx = -1;
        for (int i = 1; i <= N; i++) {
            if (maxVal < cnt[i]) {
                maxVal = cnt[i];
                maxIdx = i;
            }
        }
        rem[maxIdx] = true;
        for (int e : edges[maxIdx]) {
            if (!act[e]) continue;
            act[e] = false;
            for (int v : { trps[e].a, trps[e].b, trps[e].c }) cnt[v]--;
            rcnt--;
        }
    }

    for (int i = 1; i <= N; i++) if (!rem[i]) ans[N].push_back(i);
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> N;
        solve(N);
        cout << ans[N].size() << '\n';
        for (int v : ans[N]) cout << v << ' ';
        cout << '\n';
    }
}