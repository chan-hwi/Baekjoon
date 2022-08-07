#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct pos { int y, x; };
struct fan { int y, x, d; };

int R, C, K, W, num, cy, cx, t;
int dy[4] = { 0, 0, -1, 1 };
int dx[4] = { 1, -1, 0, 0 };
int board[21][21];
int tmp[21][21][4];
bool visit[21][21];
bool wall[21][21][4];
vector<pos> poses;
vector<fan> fans;

void fanOp(int i) {
    num = 5;
    t = fans[i].d;
    cy = fans[i].y + dy[t], cx = fans[i].x + dx[t];
    fill(&visit[0][0], &visit[20][21], false);
    queue<pos> q;
    visit[cy][cx] = true;
    board[cy][cx] += num--;
    q.push({ cy, cx });
    while (!q.empty() && num) {
        int curSize = q.size();
        for (int j = 0; j < curSize; j++) {
            int y = q.front().y, x = q.front().x;
            q.pop();
            for (int d : { (t + 2) % 4, (-((t + 2) % 4) + 5) % 4, -1 }) {
                int ny = y, nx = x;
                if (d != -1) {
                    ny += dy[d], nx += dx[d];
                    if (wall[y][x][d]) continue;
                    if (ny < 1 || ny > R || nx < 1 || nx > C) continue;
                }
                if (wall[ny][nx][t]) continue;
                ny += dy[t], nx += dx[t];
                if (ny < 1 || ny > R || nx < 1 || nx > C) continue;
                if (visit[ny][nx]) continue;
                board[ny][nx] += num;
                visit[ny][nx] = true;
                q.push({ ny, nx });
            }
        }
        num--;
    }
}

void spreadHeat() {
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            for (int d = 0; d < 4; d++) {
                tmp[i][j][d] = 0;
                if (wall[i][j][d]) continue;
                int ny = i + dy[d], nx = j + dx[d];
                if (ny < 1 || ny > R || nx < 1 || nx > C) continue;
                if (board[i][j] < board[ny][nx]) continue;
                tmp[i][j][d] = (board[i][j] - board[ny][nx]) / 4;
            }
        }
    }

    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            for (int d = 0; d < 4; d++) {
                int ny = i + dy[d], nx = j + dx[d];
                if (ny < 1 || ny > R || nx < 1 || nx > C) continue;
                board[ny][nx] += tmp[i][j][d];
                board[i][j] -= tmp[i][j][d];
            }
        }
    }

    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            if (i == 1 || i == R || j == 1 || j == C) {
                if (board[i][j]) board[i][j]--;
            }
        }
    }
}

bool check() {
    for (pos& p : poses) {
        if (board[p.y][p.x] < K) return false;
    }
    return true;
}

int solve() {
    int step = 0;
    while (step <= 100) {
        for (int i = 0; i < fans.size(); i++) fanOp(i);
        spreadHeat();
        step++;
        if (check()) return step;
    }
    return step;
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> R >> C >> K;
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            cin >> num;
            if (num && num < 5) {
                fans.push_back({ i, j, num - 1 });
            } else if (num) poses.push_back({ i, j });
        }
    }
    cin >> W;
    while (W--) {
        cin >> cy >> cx >> t;
        if (!t) {
            wall[cy][cx][2] = wall[cy - 1][cx][3] = true;
        } else {
            wall[cy][cx][0] = wall[cy][cx + 1][1] = true;
        }
    }

    cout << solve() << '\n';
}