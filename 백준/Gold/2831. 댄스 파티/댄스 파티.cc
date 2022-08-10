#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, num, ans;
vector<int> nums[2][2];

void solve(vector<int>& sa, vector<int>& la) {
    sort(sa.begin(), sa.end());
    sort(la.begin(), la.end());

    int i = 0, j = 0;
    while (i < sa.size() && j < la.size()) {
        if (sa[i] < la[j]) {
            ans++;
            i++;
        }
        j++;
    }
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < N; j++) {
            cin >> num;
            nums[i][num > 0].push_back(abs(num));
        }
    }
    solve(nums[0][1], nums[1][0]);
    solve(nums[1][1], nums[0][0]);
    cout << ans << '\n';
}