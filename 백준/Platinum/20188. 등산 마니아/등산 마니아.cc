#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

int N, a, b;
ll sum;
int cnt[300001];
vector<int> edges[300001];

ll dfs(int i, int p = -1) {
    ll cur = 0, sumSq = 0, sqSum = 0;
    for (int e : edges[i]) {
        if (e == p) continue;
        cur += dfs(e, i);
        sumSq += cnt[e];
        sqSum += (ll)cnt[e] * cnt[e];
    }

    cnt[i] = sumSq + 1;
    cur += -(sumSq * sumSq - sqSum) / 2 + (N - cnt[i]);
    if (i == 1) return 0;
    sum += cur;
    return cur;
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N;
    for (int i = 0; i < N - 1; i++) {
        cin >> a >> b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    dfs(1);
    cout << sum << '\n';
}