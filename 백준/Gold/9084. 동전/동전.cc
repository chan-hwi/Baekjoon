#include <iostream>
using namespace std;

int T, N, M;
int coins[20], dp[10001];

int main() {
    cin >> T;
    while (T--) {
        cin >> N;
        for (int i = 0; i < N; i++) cin >> coins[i];
        cin >> M;
        fill_n(dp, M + 1, 0);
        for (int i = 0; i < N; i++) {
            dp[coins[i]]++;
            for (int j = coins[i] + 1; j <= M; j++) {
                dp[j] += dp[j - coins[i]];
            }
        }

        cout << dp[M] << '\n';
    }
}