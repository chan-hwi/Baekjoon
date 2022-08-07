#include <iostream>
using namespace std;

int H, W;
int g[20][20][20][20];
bool v[401];
char board[20][20];

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> H >> W;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cin >> board[i][j];
        }
    }
    for (int h = 1; h <= H; h++) {
        for (int w = 1; w <= W; w++) {
            for (int i = 0; i + h <= H; i++) {
                for (int j = 0; j + w <= W; j++) {
                    fill_n(v, 401, false);
                    for (int y = i; y < i + h; y++) {
                        for (int x = j; x < j + w; x++) {
                            if (board[y][x] == 'X') continue;
                            int p[4][2][2] = { 
                                { { i, j }, { y - 1, x - 1 } },
                                { { i, x + 1 }, { y - 1, j + w - 1 } },
                                { { y + 1, j }, { i + h - 1, x - 1 } },
                                { { y + 1, x + 1 }, { i + h - 1, j + w - 1 } }
                            };
                            int curg = 0;
                            for (int d = 0; d < 4; d++) {
                                if (p[d][0][0] > p[d][1][0] || p[d][0][1] > p[d][1][1]) continue;
                                curg ^= g[p[d][0][0]][p[d][0][1]][p[d][1][0]][p[d][1][1]];
                            }
                            v[curg] = true;
                        }
                    }
                    for (int k = 0; k < 401; k++) {
                        if (!v[k]) {
                            g[i][j][i + h - 1][j + w - 1] = k;
                            break;
                        }
                    }
                }
            }
        }
    }
    cout << (g[0][0][H - 1][W - 1] ? "First" : "Second") << '\n';
}