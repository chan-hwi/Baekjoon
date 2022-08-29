#include <iostream>
#include <vector>
#include <queue>
#define INF 987654321
using namespace std;

struct Node { int i, w1, w2; };

struct cmp {
    bool operator() (const Node &n1, const Node &n2) {
        return n1.w2 > n2.w2;
    }
};

int N, ans = INF;
int W[20][180];
char edges[2][20][20];
priority_queue<Node, vector<Node>, cmp> pq;

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

    fill(&W[0][0], &W[19][180], 1000);
    pq.push({ 0, 0, 0 });
    W[0][0] = 0;
    while (!pq.empty()) {
        Node n = pq.top();
        pq.pop();

        if (W[n.i][n.w1] < n.w2) continue;
        if (n.i == 1) {
            ans = min(ans, n.w1 * n.w2);
            continue;
        }
        for (int j = 0; j < N; j++) {
            Node nn = { j, n.w1 + (edges[0][n.i][j] - '0'), n.w2 + (edges[1][n.i][j] - '0') };
            if (edges[0][n.i][j] == '.' || nn.w1 >= 180 || W[j][nn.w1] <= nn.w2) continue;
            W[j][nn.w1] = nn.w2;
            pq.push(nn);
        }
    }
    cout << (ans == INF ? -1 : ans) << '\n';
}