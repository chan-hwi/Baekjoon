#include <iostream>
#define N   10
#define INF 987654321
using namespace std;

int cur, ans = INF;
int cnt[5] = { 5, 5, 5, 5, 5 };
int board[10][10];

void solve(int i = 0, int j = 0) {
    if (i >= N) { ans = min(ans, cur); return; }
    if (!board[i][j]) { solve(i + (j == N - 1), (j + 1) % N); return; }
    for (int k = 0; k < 5; k++) {
        if (!cnt[k] || i + k >= N || j + k >= N) continue;
        bool pos = true;
        for (int y = i; y <= i + k; y++) {
            for (int x = j; x <= j + k; x++) {
                if (!board[y][x]) { pos = false; break; }
            }
            if (!pos) break;
        }
        if (!pos) continue;
        for (int y = i; y <= i + k; y++) {
            for (int x = j; x <= j + k; x++) {
                board[y][x] = 0;
            }
        }
        cnt[k]--;   cur++;
        solve(i + (j == N - 1), (j + 1) % N);
        cnt[k]++;   cur--;
        for (int y = i; y <= i + k; y++) {
            for (int x = j; x <= j + k; x++) {
                board[y][x] = 1;
            }
        }
    }
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> board[i][j];
        }
    }

    solve();
    cout << (ans == INF ? -1 : ans) << '\n';
}