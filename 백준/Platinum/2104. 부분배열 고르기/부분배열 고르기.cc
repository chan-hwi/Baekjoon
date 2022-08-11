#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef long long ll;

int N;
ll ans;
ll sum[100001];
map<int, vector<int>> sorted;
map<int, bool> indices;

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> sum[i];
        sorted[sum[i]].push_back(i);
    }
    for (int i = 2; i <= N; i++) sum[i] += sum[i - 1];
    for (auto& cur : sorted) {
        int a = cur.first;
        for (int& b : cur.second) {
            auto lo = indices.lower_bound(b);
            int l = (lo == indices.begin() ? 0 : prev(lo)->first);
            int r = (lo == indices.end() ? N : lo->first - 1);
            ans = max(ans, (sum[r] - sum[l]) * a);
        }
        for (int& b : cur.second) indices[b] = true;
    }
    cout << ans << '\n';
}