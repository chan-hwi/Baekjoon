#include <iostream>
#define INF 987654321
using namespace std;

int T, N, M, K, num;
int cc[31], dp[31];

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> N >> M >> K;
        for (int i = 1; i <= M; i++) cin >> cc[i];
        fill_n(dp, M + 1, INF);
        dp[0] = 0;
        for (int i = 1; i <= N; i++) {
            cin >> num;
            for (int j = 0; j <= M; j++) {
                if (j != num) {
                    dp[num] = min(dp[num], dp[j] + K);
                    dp[j] = min(INF, dp[j] + cc[num]);
                }
            }
        }
        int ans = INF;
        for (int i = 0; i <= M; i++) ans = min(ans, dp[i]);
        cout << ans << '\n';
    }
}