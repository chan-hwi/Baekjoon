#include <iostream>
#include <queue>
using namespace std;

int L, Ml, Mk, C;
int nums[3000000];
queue<int> q;

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> L >> Ml >> Mk >> C;
    for (int i = 0; i < L; i++) cin >> nums[i];
    int curSub = 0;
    for (int i = 0; i < L; i++) {
        if (!q.empty() && q.front() == i) {
            q.pop();
            curSub--;
        }
        if (nums[i] > (min(i + 1, Ml) - curSub) * Mk) {
            if (!C) { cout << "NO" << '\n'; return 0; }
            C--;
            curSub++;
            q.push(i + Ml);
        }
    }
    cout << "YES" << '\n';
}