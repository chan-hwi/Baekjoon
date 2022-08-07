#include <iostream>
using namespace std;

int N, M, K, p, y, x, ans, cd, cur = 6;
int dy[4] = { 0, 1, 0, -1 };
int dx[4] = { 1, 0, -1, 0 };
int board[20][20], score[20][20];
int dice[4][3];
int idx[2][4][2] = {
    { { 1, 0 }, { 1, 1 }, { 1, 2 }, { 3, 1 } },
    { { 0, 1 }, { 1, 1,}, { 2, 1 }, { 3, 1 } }
};
bool visit[20][20];

void rotate(int d, int l, int a) {
    int e = l + 3 * a;
    int tmp = dice[idx[d][e][0]][idx[d][e][1]];
    for (int j = e; j != l; j -= a) {
        dice[idx[d][j][0]][idx[d][j][1]] = dice[idx[d][j - a][0]][idx[d][j - a][1]];
    }
    dice[idx[d][l][0]][idx[d][l][1]] = tmp;
}

void dfs(int i, int j) {
    score[p / M][p % M]++;
    for (int d = 0; d < 4; d++) {
        int ny = i + dy[d], nx = j + dx[d];
        if (ny < 0 || ny >= N || nx < 0 || nx >= M) continue;
        if (visit[ny][nx] || board[i][j] != board[ny][nx]) continue;
        visit[ny][nx] = true;
        score[ny][nx] = -p;
        dfs(ny, nx);
    }
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N >> M >> K;
    dice[0][1] = 2, dice[1][0] = 4, dice[1][1] = 1, dice[1][2] = 3, dice[2][1] = 5, dice[3][1] = 6;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> board[i][j];
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (!visit[i][j]) {
                p = i * M + j;
                visit[i][j] = true;
                dfs(i, j);
                score[i][j] *= board[i][j];
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (score[i][j] <= 0) {
                p = -score[i][j];
                score[i][j] = score[p / M][p % M];
            }
        }
    }

    while (K--) {
        int ny = y + dy[cd], nx = x + dx[cd];
        if (ny < 0 || ny >= N || nx < 0 || nx >= M) {
            cd = (cd + 2) % 4; 
            K++; 
            continue; 
        }
        ans += score[ny][nx];
        rotate(cd % 2, cd < 2 ? 0 : 3, cd < 2 ? 1 : -1);
        cur = dice[3][1];
        if (cur > board[ny][nx]) cd = (cd + 1) % 4;
        else if (cur < board[ny][nx]) cd = (cd + 3) % 4;
        y = ny, x = nx;
    }
    cout << ans << '\n';
}