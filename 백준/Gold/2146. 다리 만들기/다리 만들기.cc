#include <iostream>
#include <queue>
#define INF 987654321
using namespace std;

struct pos { int y, x; };

int N, ci, ans = INF;
int dy[4] = { 0, 0, 1, -1 };
int dx[4] = { 1, -1, 0, 0 };
int visit[100][100], grp[100][100];
bool board[100][100];
queue<pos> nq;

void makeGrp(int i, int j) {
    queue<pos> q;
    q.push({ i, j });
    while (!q.empty()) {
        pos cp = q.front();
        q.pop();
        for (int d = 0; d < 4; d++) {
            int ny = cp.y + dy[d], nx = cp.x + dx[d];
            if (ny < 0 || ny >= N || nx < 0 || nx >= N) continue;
            if (visit[ny][nx] != -1) continue;
            if (board[ny][nx]) {
                visit[ny][nx] = 0;
                q.push({ ny, nx });
            } else {
                visit[ny][nx] = 1;
                nq.push({ ny, nx });
            }
            grp[ny][nx] = ci;
        }
    }
}

void bfs() {
    while (!nq.empty()) {
        pos cp = nq.front();
        nq.pop();
        
        for (int d = 0; d < 4; d++) {
            int ny = cp.y + dy[d], nx = cp.x + dx[d];
            if (ny < 0 || ny >= N || nx < 0 || nx >= N) continue;
            if (visit[ny][nx] != -1) {
                if (grp[ny][nx] != grp[cp.y][cp.x]) ans = min(ans, visit[ny][nx] + visit[cp.y][cp.x]);
                continue;
            }
            grp[ny][nx] = grp[cp.y][cp.x];
            visit[ny][nx] = visit[cp.y][cp.x] + 1;
            nq.push({ ny, nx });
        }
    }
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> board[i][j];
        }
    }

    fill(&visit[0][0], &visit[N - 1][N], -1);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] && !grp[i][j]) {
                visit[i][j] = 0;
                grp[i][j] = ++ci;
                makeGrp(i, j);
            }
        }
    }

    bfs();
    cout << ans << '\n';
}