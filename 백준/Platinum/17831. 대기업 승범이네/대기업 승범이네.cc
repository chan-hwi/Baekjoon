#include <iostream>
#include <vector>
using namespace std;

int N, a;
int nums[200001];
int dp[200001][2];
vector<int> edges[200001];

int solve(int i, bool marked = false) {
    int& ret = dp[i][marked];
    if (ret != -1) return ret;
    int sum = 0;
    for (int e : edges[i]) sum += solve(e);
    if (marked) return ret = sum;
    
    int maxVal = sum;
    for (int e : edges[i]) {
        maxVal = max(maxVal, sum - solve(e) + solve(e, true) + nums[i] * nums[e]);
    }
    return ret = maxVal;
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N;
    fill(&dp[0][0], &dp[N + 1][2], -1);
    for (int i = 2; i <= N; i++) {
        cin >> a;
        edges[a].push_back(i);
    }
    for (int i = 1; i <= N; i++) cin >> nums[i];
    cout << solve(1) << '\n';
}