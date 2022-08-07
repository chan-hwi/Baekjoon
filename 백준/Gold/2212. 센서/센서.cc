#include <iostream>
#include <algorithm>
using namespace std;

int N, K, ans;
int nums[10000];

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N >> K;
    if (N == 1) {
        cout << 0 << '\n';
        return 0;
    }
    for (int i = 0; i < N; i++) cin >> nums[i];
    sort(nums, nums + N);
    for (int i = 0; i < N - 1; i++) ans += (nums[i] = nums[i + 1] - nums[i]);
    sort(nums, nums + N - 1);
    
    int j = N - 2;
    int k = min(K - 1, N - 1);
    while (k--) ans -= nums[j--];
    cout << ans << '\n';
}