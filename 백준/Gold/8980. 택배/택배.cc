#include <iostream>
#include <algorithm>
using namespace std;

typedef pair<int, int> pii;

int N, C, M, u, v, w, ans;
int cap[2001];
pair<pii, int> boxes[10000];

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N >> C >> M;
    for (int i = 0; i < M; i++) {
        cin >> u >> v >> w;
        boxes[i] = { { v, u }, w };
    }
    sort(boxes, boxes + M);

    for (int i = 0; i < M; i++) {
        auto& b = boxes[i];
        int l = b.first.second, r = b.first.first - 1;
        int amt = min(C, b.second);
        for (int k = l; k <= r; k++) amt = min(amt, C - cap[k]);
        if (!amt) continue;
        for (int k = l; k <= r; k++) cap[k] += amt;
        ans += amt;
    }
    cout << ans << '\n';
}