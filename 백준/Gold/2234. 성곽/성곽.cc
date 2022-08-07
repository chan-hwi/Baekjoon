#include <iostream>
using namespace std;

int N, M, ci, maxVal, mergeMax;
int dy[4] = { 0, -1, 0, 1 };
int dx[4] = { -1, 0, 1, 0 };
int grpCnt[2501];
int board[50][50], grp[50][50], cnt[50][50];

void solve(int i, int j) {
    cnt[i][j] = 1;
    for (int d = 0; d < 4; d++) {
        int ny = i + dy[d], nx = j + dx[d];
        if (ny < 0 || ny >= N || nx < 0 || nx >= M) continue;
        if (grp[ny][nx] || (board[i][j] & (1 << d))) continue;
        grp[ny][nx] = ci;
        solve(ny, nx);
        cnt[i][j] += cnt[ny][nx];
    }
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> M >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> board[i][j];
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (grp[i][j]) continue;
            grp[i][j] = ++ci;
            solve(i, j);
            maxVal = max(maxVal, grpCnt[ci] = cnt[i][j]);
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int d = 0; d < 4; d++) {
                int ny = i + dy[d], nx = j + dx[d];
                if (ny < 0 || ny >= N || nx < 0 || nx >= M) continue;
                if (!(board[i][j] & (1 << d)) || grp[i][j] == grp[ny][nx]) continue;
                mergeMax = max(mergeMax, grpCnt[grp[i][j]] + grpCnt[grp[ny][nx]]);
            }
        }
    }

    cout << ci << '\n';
    cout << maxVal << '\n';
    cout << mergeMax << '\n';
}