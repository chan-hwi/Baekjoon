#include <iostream>
using namespace std;

typedef long long ll;

int N;
int cnt[10] = { 6, 2, 5, 5, 4, 5, 6, 3, 7, 5 };
int cntSum[15];
ll dp[15][106];
string str;

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> str;
    N = str.size();
    fill(&dp[0][0], &dp[N - 1][106], -1);
    for (int i = N - 1; i >= 0; i--) cntSum[i] = (i != N - 1 ? cntSum[i + 1] : 0) + cnt[str[i] - '0'];
    
    dp[0][2] = 1;
    dp[0][3] = 7;
    dp[0][4] = 4;
    dp[0][5] = 2;
    dp[0][6] = 0;
    dp[0][7] = 8;
    
    ll p10 = 10;
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k <= 105; k++) {
                if (cnt[j] > k || dp[i - 1][k - cnt[j]] == -1 || dp[i][k] != -1) continue;
                dp[i][k] = p10 * j + dp[i - 1][k - cnt[j]];
            }
        }
        p10 *= 10;
    }

    p10 = 10;
    ll cur = 0;
    int a = str[N - 1] - '0';
    for (int j = a + 1; j < 10; j++) {
        if (cnt[a] == cnt[j]) {
            cout << j - a << '\n';
            return 0;
        }
    }
    for (int i = N - 2; i >= 0; i--) {
        cur += p10 / 10 * (str[i + 1] - '0');
        ll rem = p10 - cur;
        ll curCnt = rem;
        for (int j = str[i] - '0' + 1; j < 10; j++) {
            ll val = dp[N - i - 2][cntSum[i] - cnt[j]];
            if (cnt[j] <= cntSum[i] && val != -1) {
                cout << curCnt + val << '\n';
                return 0;
            }
            curCnt += p10;
        }
        p10 *= 10;
    }
    cur += p10 / 10 * (str[0] - '0');
    ll rem = p10 - cur;
    cout << rem + dp[N - 1][cntSum[0]] << '\n';
}