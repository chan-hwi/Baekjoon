#include <iostream>
#include <deque>
using namespace std;

int N, M;
int dy[4] = { 1, -1, 1, -1 };
int dx[4] = { 1, -1, -1, 1 };
int ly[4] = { 0, -1, 0, -1 };
int lx[4] = { 0, -1, -1, 0 };
int visit[501][501];
char board[501][501];
deque<int> dq;

int bfs() {
    fill(&visit[0][0], &visit[N][M + 1], -1);
    dq.push_front(0);
    visit[0][0] = 0;
    while (!dq.empty()) {
        int y = dq.front() / (M + 1), x = dq.front() % (M + 1);
        dq.pop_front();
        if (y == N && x == M) return visit[y][x];
        for (int d = 0; d < 4; d++) {
            int ny = y + dy[d], nx = x + dx[d];
            int ay = y + ly[d], ax = x + lx[d];
            if (ny < 0 || ny > N || nx < 0 || nx > M) continue;

            int val = visit[y][x] + (d < 2 && board[ay][ax] == '/' || d >= 2 && board[ay][ax] == '\\');
            if (visit[ny][nx] != -1 && visit[ny][nx] <= val) continue;
            visit[ny][nx] = val;
            if (visit[y][x] == val) dq.push_front(ny * (M + 1) + nx);
            else dq.push_back(ny * (M + 1) + nx);
        }
    }
    return -1;
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N >> M;
    for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) cin >> board[i][j];
    int ans = bfs();
    if (ans != -1) cout << ans << '\n';
    else cout << "NO SOLUTION" << '\n';
}