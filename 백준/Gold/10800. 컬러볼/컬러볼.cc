#include <iostream>
#include <vector>
using namespace std;

int N, totalCnt, s;
int cnt[200001], colors[200001], ans[200001];
vector<int> sizes[2001];

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> colors[i] >> s;
        sizes[s].push_back(i);
    }
    for (int i = 1; i <= 2000; i++) {
        for (int e : sizes[i]) {
            ans[e] = totalCnt - cnt[colors[e]];
        }
        totalCnt += i * sizes[i].size();
        for (int e : sizes[i]) {
            cnt[colors[e]] += i;
        }
    }
    for (int i = 1; i <= N; i++) cout << ans[i] << '\n';
}