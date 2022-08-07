#include <iostream>
#include <algorithm>
using namespace std;

int L, K, C;
int nums[10002];

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> L >> K >> C;
    for (int i = 1; i <= K; i++) cin >> nums[i];
    nums[K + 1] = L;
    sort(nums + 1, nums + K + 1);
    K = unique(nums, nums + K + 2) - nums;
    int l = L - nums[K - 2] - 1, r = L;
    while (l + 1 != r) {
        int m = l + r >> 1;
        int j = K - 1;
        for (int k = 0; k < C; k++) {
            int sum = 0;
            while (j && sum + nums[j] - nums[j - 1] <= m) {
                sum += nums[j] - nums[j - 1];
                j--;
            }
        }
        if (nums[j] <= m) r = m;
        else l = m;
    }
    int j = K - 1;
    for (int k = 0; k < C; k++) {
        int sum = 0;
        while (j && sum + nums[j] - nums[j - 1] <= r) {
            sum += nums[j] - nums[j - 1];
            j--;
        }
    }
    cout << r << ' ' << (nums[(!j ? 1 : j)]) << '\n';
}