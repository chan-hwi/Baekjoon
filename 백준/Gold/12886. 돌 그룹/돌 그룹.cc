#include <iostream>
#include <queue>
using namespace std;

struct point { int l, r; };

int a, b, c, sum;
bool visit[1501][1501];
queue<point> q;

bool bfs() {
    sum = a + b + c;
    int l = min(a, min(b, c)), r = max(a, max(b, c));
    visit[l][r] = true;
    q.push({ l, r });
    while (!q.empty()) {
        l = q.front().l, r = q.front().r;
        int cur[3] = { l, sum - l - r, r };
        q.pop();
        if (cur[0] == cur[1] && cur[1] == cur[2]) return true;
        for (int i = 0; i < 2; i++) {
            for (int j = i + 1; j < 3; j++) {
                cur[j] -= cur[i];
                cur[i] <<= 1;
                a = min(cur[0], min(cur[1], cur[2]));
                c = max(cur[0], max(cur[1], cur[2]));
                if (!visit[a][c]) {
                    visit[a][c] = true;
                    q.push({ a, c });
                }
                cur[i] >>= 1;
                cur[j] += cur[i];
            }
        }
    }
    return false;
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> a >> b >> c;
    cout << bfs() << '\n';
}