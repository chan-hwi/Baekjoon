#include <iostream>
#include <deque>
using namespace std;

int N, M;
int nums[1000000];
deque<int> dq;

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N >> M;
    for (int i = 0; i < N; i++) cin >> nums[i];

    for (int i = 0; i < M * 2 - 2; i++) {
        while (!dq.empty() && nums[dq.back()] <= nums[i]) dq.pop_back();
        dq.push_back(i);
    }
    for (int i = M * 2 - 2; i < N; i++) {
        while (!dq.empty() && nums[dq.back()] <= nums[i]) dq.pop_back();
        dq.push_back(i);
        int p = i - M * 2 + 2;
        while (!dq.empty() && dq.front() < p) dq.pop_front();
        cout << nums[dq.front()] << ' ';
    }
    cout << '\n';
}