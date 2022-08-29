#include <iostream>
#include <queue>
#define INF 987654321
using namespace std;

struct Node { int i, bm, w[2]; };

int N, ans = INF;
bool visit[20][1 << 20];
char edges[2][20][20];
queue<Node> q;

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N;
    for (int k = 0; k < 2; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> edges[k][i][j];
            }
        }
    }

    q.push({ 0, 1, { 0, 0 } });
    visit[0][1] = true;
    while (!q.empty()) {
        Node n = q.front();
        q.pop();

        for (int j = 0; j < N; j++) {
            Node nn = { j, n.bm | (1 << j), { n.w[0] + (edges[0][n.i][j] - '0'), n.w[1] + (edges[1][n.i][j] - '0') } };
            if (edges[0][n.i][j] == '.' || visit[j][nn.bm]) continue;
            if (j == 1) {
                ans = min(ans, nn.w[0] * nn.w[1]);
                continue;
            }
            q.push(nn);
            visit[j][nn.bm] = true;
        }
    }
    cout << (ans == INF ? -1 : ans) << '\n';
}