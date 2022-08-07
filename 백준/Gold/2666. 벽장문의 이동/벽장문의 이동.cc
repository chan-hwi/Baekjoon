#include <iostream>
#include <queue>
using namespace std;

struct pos { int a, b, k; };

int N, K, a, b;
int nums[20];
int d1[4] = { -1, 1, 0, 0 };
int d2[4] = { 0, 0, -1, 1 };
bool visit[20][21][21];
queue<pos> q;

int bfs() {
    int curK = 0;
    while (curK < K && (a == nums[curK] || b == nums[curK])) curK++;
    if (curK == K) return 0;
    q.push({ a, b, curK });
    visit[0][a][b] = true;

    int t = 1;
    while (!q.empty()) {
        int curSize = q.size();
        for (int i = 0; i < curSize; i++) {
            pos p = q.front();
            q.pop();
            for (int d = 0; d < 4; d++) {
                int newPos[2] = { p.a + d1[d], p.b + d2[d] };
                if (newPos[0] < 1 || newPos[0] >= newPos[1] || newPos[1] <= newPos[0] || newPos[1] > N) continue;
                int curK = p.k;
                while (curK < K && (newPos[0] == nums[curK] || newPos[1] == nums[curK])) curK++;
                if (curK == K) return t;
                if (visit[curK][newPos[0]][newPos[1]]) continue;
                visit[curK][newPos[0]][newPos[1]] = true;
                q.push({ newPos[0], newPos[1], curK });
            }
        }
        t++;
    }
    return -1;
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N >> a >> b >> K;
    for (int i = 0; i < K; i++) cin >> nums[i];
    cout << bfs() << '\n';
}