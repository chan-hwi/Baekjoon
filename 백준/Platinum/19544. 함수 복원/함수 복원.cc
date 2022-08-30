#include <iostream>
#include <vector>
#define MOD 1000000007
using namespace std;

typedef long long ll;

int N, ans = 1;
int grp[500], cnt[500], edge[500], fact[501];
bool visit[500];
bool mat[500][500];

void dfs(int i) {
    if (visit[i]) return;
    visit[i] = true;
    ans = ((ll)ans * fact[cnt[i] - 1]) % MOD;
    if (edge[i] != i) ans = ((ll)ans * cnt[edge[i]]) % MOD;
    dfs(edge[i]);
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N;
    fact[0] = 1;
    for (int i = 1; i <= N; i++) fact[i] = ((ll)i * fact[i - 1]) % MOD;
    for (int i = 0; i < N; i++) {
        grp[i] = edge[i] = i; cnt[i] = 1;
        for (int j = 0; j < N; j++) {
            cin >> mat[i][j];
        }
    }

    for (int i = 0; i < N - 1; i++) {
        if (grp[i] != i) continue;
        for (int j = i + 1; j < N; j++) {
            if (mat[i][j] && mat[j][i]) {
                grp[j] = i;
                cnt[i]++;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        if (grp[i] != i) continue;
        for (int j = 0; j < N; j++) {
            if (i == j) continue;
            bool pos = true;
            for (int k = 0; k < N; k++) {
                if (j != k && mat[i][k] != mat[j][k]) {
                    pos = false;
                    break;
                }
            }
            if (pos) edge[j] = i;
        }
    }

    for (int i = 0; i < N; i++) {
        if (grp[i] == i) dfs(i);
    }

    cout << ans << '\n';
}