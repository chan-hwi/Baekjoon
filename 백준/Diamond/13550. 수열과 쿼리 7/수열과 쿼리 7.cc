#include <iostream>
#include <cmath>
#include <list>
#include <algorithm>
#define MAX 1000
using namespace std;

struct qr { int l, r, idx; };

int N, K, M, srN, x, y;
int ans[100000], nums[100001], cnt[1010001], grp[1001];
qr qrs[100000];
list<int> dq[1000001];

bool cmp(const qr &q1, const qr &q2) {
    int g1 = q1.l / srN, g2 = q2.l / srN;
    return (g1 == g2 ? q1.r < q2.r : g1 < g2);
}

void update(int val, int diff) {
    cnt[val] += diff;
    grp[val / MAX] += diff;
}

void Add(int curIdx, bool isBack) {
    auto& cdq = dq[nums[curIdx]];
    if (!cdq.empty()) update(cdq.back() - cdq.front(), -1);
    if (isBack) cdq.push_back(curIdx);
    else cdq.push_front(curIdx);
    update(cdq.back() - cdq.front(), 1);
}

void Sub(int curIdx, bool isBack) {
    auto& cdq = dq[nums[curIdx]];
    update(cdq.back() - cdq.front(), -1);
    if (isBack) cdq.pop_back();
    else cdq.pop_front();
    if (!cdq.empty()) update(cdq.back() - cdq.front(), 1);
}

int maxDist() {
    int curGrp;
    for (curGrp = MAX; curGrp >= 0; curGrp--) if (grp[curGrp]) break;
    for (int i = MAX - 1; i >= 0; i--) if (cnt[curGrp * MAX + i] > 0) return curGrp * MAX + i;
    return 0;
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N >> K;
    srN = sqrt(N);
    for (int i = 1; i <= N; i++) cin >> nums[i];
    for (int i = 1; i <= N; i++) nums[i] = (nums[i - 1] + nums[i] % K) % K;
    cin >> M;
    for (int i = 0; i < M; i++) {
        cin >> x >> y;
        qrs[i] = { x - 1, y, i };
    }
    sort(qrs, qrs + M, cmp);

    x = 1, y = 1;
    for (int i = 0; i < M; i++) {
        auto& [l, r, idx] = qrs[i];
        while (l < x) Add(--x, false);
        while (y <= r) Add(y++, true);
        while (x < l) Sub(x++, false);
        while (r + 1 < y) Sub(--y, true);
        ans[idx] = maxDist();
    }
    
    for (int i = 0; i < M; i++) cout << ans[i] << '\n';
}