#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

int a, b, c, d, x, y, mx, my;
int p[4][2][2];
int xRange[2], yRange[2], tRange[2];

ll getSum(int t, int s) {
    int l[2][2];
    if (s <= x + min(a, c)) { l[0][0] = 1, l[0][1] = -x + 1; }
    else if (s <= x + max(a, c)) { l[0][0] = 0, l[0][1] = min(a, c) + 1; }
    else { l[0][0] = -1, l[0][1] = x + a + c + 1; }
    if (s <= y + min(b, d)) { l[1][0] = 1, l[1][1] = -y + 1; }
    else if (s <= y + max(b, d)) { l[1][0] = 0, l[1][1] = min(b, d) + 1; }
    else { l[1][0] = -1, l[1][1] = y + b + d + 1; }

    ll u = l[0][0] * l[1][0];
    ll v = (ll)l[0][0] * l[1][1] + (ll)l[1][0] * l[0][1];
    ll w = (ll)l[0][1] * l[1][1];

    return u * t * (t + 1) * (t * 2 + 1) / 6 + v * t * (t + 1) / 2 + w * t;
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            cin >> p[i][j][0] >> p[i][j][1];
        }
    }
    a = min(p[1][0][0], p[2][0][0]) - max(p[1][1][0], p[2][1][0]);
    b = min(p[0][1][1], p[1][1][1]) - max(p[0][0][1], p[1][0][1]);
    c = min(p[0][1][0], p[3][1][0]) - max(p[0][0][0], p[3][0][0]);
    d = min(p[2][0][1], p[3][0][1]) - max(p[2][1][1], p[3][1][1]);
    x = max(p[0][0][0], p[3][0][0]) - min(p[1][0][0], p[2][0][0]);
    y = max(p[0][0][1], p[1][0][1]) - min(p[2][0][1], p[3][0][1]);
    if (a < 0 || b < 0 || c < 0 || d < 0) {
        cout << 0 << '\n';
        return 0;
    }
    xRange[0] = x, xRange[1] = a + c + x;
    yRange[0] = y, yRange[1] = b + d + y;
    tRange[0] = max(xRange[0], yRange[0]);
    tRange[1] = min(xRange[1], yRange[1]);
    ll sum = 0;
    int dxy[4] = { x + min(a, c), x + max(a, c), y + min(b, d), y + max(b, d) };
    int k[5];
    for (int i = 0; i < 4; i++) k[i] = (dxy[i] >= tRange[0] && dxy[i] <= tRange[1] ? dxy[i] : -1);
    k[4] = tRange[1];
    sort(k, k + 4);
    int pidx = tRange[0] - 1;
    for (int i = 0; i < 5; i++) {
        if (k[i] >= pidx + 1) {
            sum += getSum(k[i], k[i]) - getSum(pidx, k[i]);
            pidx = k[i];
        }
    }
    cout << sum << '\n';
}