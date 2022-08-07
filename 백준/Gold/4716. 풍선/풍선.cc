#include <iostream>
#include <algorithm>
using namespace std;

int N;
int cnt[2], nums[1000], sorted[1000];
int dist[1000][2];

bool cmp(int i, int j) {
    return abs(dist[i][0] - dist[i][1]) > abs(dist[j][0] - dist[j][1]);
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    while (true) {
        int ans = 0;
        cin >> N >> cnt[0] >> cnt[1];
        if (!N && !cnt[0] && !cnt[1]) break;
        for (int i = 0; i < N; i++) cin >> nums[i] >> dist[i][0] >> dist[i][1];
        for (int i = 0; i < N; i++) sorted[i] = i;
        sort(sorted, sorted + N, cmp);
        for (int i = 0; i < N; i++) {
            int j = sorted[i];
            bool s = dist[j][0] > dist[j][1];
            int a = min(nums[j], cnt[s]), b = nums[j] - a;
            ans += a * dist[j][s] + b * dist[j][!s];
            cnt[s] -= a;
            cnt[!s] -= b;
        }
        cout << ans << '\n';
    }
}