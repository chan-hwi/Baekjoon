#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M, K;
int nums[50];
bool ans[50];
vector<int> dists;

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N >> M >> K;
    for (int i = 0; i < K; i++) cin >> nums[i];
    for (int i = 0; i < K - 1; i++) {
        for (int j = i + 1; j < K; j++) {
            dists.push_back(nums[j] - nums[i]);
        }
    }
    sort(dists.begin(), dists.end());
    dists.erase(unique(dists.begin(), dists.end()), dists.end());

    for (int idx = dists.size() - 1; idx >= 0; idx--) {
        int i = dists[idx];
        int j = 0;
        ans[0] = true;
        bool pos = true;
        for (int k = 0; k < M - 1; k++) {
            int sum = 0;
            while (j < K - 1 && sum < i) {
                sum += nums[j + 1] - nums[j];
                j++;
            }
            if (sum < i) { pos = false; break; }
            ans[j] = true;
        }
        if (pos) {
            for (int n = 0; n < K; n++) cout << ans[n];
            cout << '\n';
            return 0;
        }
        fill_n(ans, K, false);
    }

    for (int i = 0; i < K; i++) cout << ans[i];
    cout << '\n';
}