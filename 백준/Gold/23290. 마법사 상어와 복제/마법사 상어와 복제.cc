#include <iostream>
#include <vector>
#define R   4
#define C   4
using namespace std;

struct fish { int y, x, d; };

int M, S, s, cy, cx, cd;
int mv[3];
int dy[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };
int dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int ds[4] = { 2, 0, 6, 4 };
int board[2][R][C], odor[R][C];
bool visit[R][C];
vector<fish> fishes[2];

int getDir(fish f) {
    for (int t = 0; t < 8; t++) {
        int nd = (f.d - t + 8) % 8;
        int ny = f.y + dy[nd], nx = f.x + dx[nd];
        if (ny < 0 || ny >= R || nx < 0 || nx >= C) continue;
        if (cy == ny && cx == nx || odor[ny][nx]) continue;
        return nd;
    }
    return -1;
}

int sharkMov(int i) {
    int y = cy, x = cx, cnt = 0;
    mv[0] = i / 16; mv[1] = i % 16 / 4; mv[2] = i % 4;
    fill(&visit[0][0], &visit[R - 1][C], false);
    for (int j = 0; j < 3; j++) {
        y += dy[ds[mv[j]]], x += dx[ds[mv[j]]];
        if (y < 0 || y >= R || x < 0 || x >= C) return -1;
        if (!visit[y][x]) cnt += board[s % 2][y][x];
        visit[y][x] = true;
    }
    return cnt;
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> M >> S;
    for (int i = 0; i < M; i++) {
        cin >> cy >> cx >> cd;
        fishes[0].push_back({ cy - 1, cx - 1, cd - 1 });
        board[0][cy - 1][cx - 1]++;
    }
    cin >> cy >> cx;
    cy--;   cx--;

    for (s = 0; s < S; s++) {
        fill(&board[(s + 1) % 2][0][0], &board[(s + 1) % 2][R - 1][C], 0);
        fishes[(s + 1) % 2].clear();
        for (fish& f : fishes[s % 2]) {
            fishes[(s + 1) % 2].push_back(f);
            board[(s + 1) % 2][f.y][f.x]++;
            board[s % 2][f.y][f.x]--;
            int nd = getDir(f);
            if (nd != -1) {
                f.y += dy[nd];
                f.x += dx[nd];
                f.d = nd;
            }
            board[s % 2][f.y][f.x]++;
        }

        int maxVal = -1, maxIdx = -1;
        for (int i = 0; i < 64; i++) {
            int curCnt = sharkMov(i);
            if (maxVal < curCnt) {
                maxVal = curCnt;
                maxIdx = i;
            }
        }

        mv[0] = maxIdx / 16, mv[1] = maxIdx % 16 / 4, mv[2] = maxIdx % 4;
        vector<bool> v(fishes[s % 2].size(), true);
        for (int i = 0; i < 3; i++) {
            cy += dy[ds[mv[i]]], cx += dx[ds[mv[i]]];
            for (int j = 0; j < fishes[s % 2].size(); j++) {
                fish f = fishes[s % 2][j];
                if (cy == f.y && cx == f.x) {
                    v[j] = false;
                    odor[f.y][f.x] = 3;
                }
            }
        }

        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                if (odor[i][j]) odor[i][j]--;
            }
        }

        for (int i = 0; i < fishes[s % 2].size(); i++) {
            if (!v[i]) continue;
            fish f = fishes[s % 2][i];
            fishes[(s + 1) % 2].push_back(f);
            board[(s + 1) % 2][f.y][f.x]++;
        }
    }

    int total = 0;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            total += board[S % 2][i][j];
        }
    }
    cout << total << '\n';
}