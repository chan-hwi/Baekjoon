#include <iostream>
using namespace std;

int N, M, K;
int ans[1000001];

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N >> M;
    K = (N + M - 1) / M;
    if (K > M) {
        cout << -1 << '\n';
        return 0;
    }

    int rem = N, idx = 1;
    for (int i = M; i; i--) {
        int cnt = min(K, rem - i + 1);
        for (int j = rem - cnt + 1; j <= rem; j++) ans[idx++] = j;
        rem -= cnt;
    }
    for (int i = N; i; i--) cout << ans[i] << ' ';
    cout << '\n';
}