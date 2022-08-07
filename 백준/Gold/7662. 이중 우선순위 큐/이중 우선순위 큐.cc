#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int T, K, num;
int nums[1000000];
bool act[1000000];
char c;

struct maxComp { bool operator()(int a, int b) { return nums[a] < nums[b]; } };
struct minComp { bool operator()(int a, int b) { return nums[a] > nums[b]; } };

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> K;
        int cnt = 0;
        fill_n(act, K, true);
        priority_queue<int, vector<int>, maxComp> maxQ;
        priority_queue<int, vector<int>, minComp> minQ;
        for (int i = 0; i < K; i++) {
            cin >> c >> num;
            if (c == 'I') {
                nums[cnt] = num;
                minQ.push(cnt);
                maxQ.push(cnt);
                cnt++;
            } else {
                while (!maxQ.empty() && !act[maxQ.top()]) maxQ.pop();
                while (!minQ.empty() && !act[minQ.top()]) minQ.pop();

                if (maxQ.empty() || minQ.empty()) continue;
                if (num == 1) {
                    act[maxQ.top()] = false;
                    maxQ.pop();
                } else {
                    act[minQ.top()] = false;
                    minQ.pop();
                }
            }
        }
        while (!maxQ.empty() && !act[maxQ.top()]) maxQ.pop();
        while (!minQ.empty() && !act[minQ.top()]) minQ.pop();
        if (maxQ.empty() || minQ.empty()) cout << "EMPTY" << '\n';
        else cout << nums[maxQ.top()] << ' ' << nums[minQ.top()] << '\n';
    }
}