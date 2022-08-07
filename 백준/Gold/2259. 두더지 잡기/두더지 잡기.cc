#include <iostream>
#include <algorithm>
#define MAX 6666
using namespace std;

typedef long long ll;

struct pos { int y, x, t; };
bool operator<(pos p1, pos p2) { return p1.t == p2.t ? (p1.y == p2.y ? p1.x < p2.x : p1.y < p2.y) : p1.t < p2.t; }

int N, S, a, b, c, ans;
int dp[MAX + 1];
pos poses[MAX + 1];

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N >> S;
    poses[0] = { 0, 0, 0 };
    for (int i = 1; i <= N; i++) {
        cin >> a >> b >> c;
        poses[i] = { a, b, c };
    }
    sort(poses, poses + N + 1);
    for (int i = 1; i <= N; i++) {
        dp[i] = -1;
        for (int j = 0; j < i; j++) {
            if (dp[j] == -1) continue;
            ll xd = poses[i].y - poses[j].y;
            ll yd = poses[i].x - poses[j].x;
            ll cd = (ll)S * (poses[i].t - poses[j].t);
            if (xd * xd + yd * yd <= cd * cd) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        ans = max(ans, dp[i]);
    }
    cout << ans << '\n';
}