#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, d ,w, ans;
vector<int> hws[1001];
priority_queue<int> pq;

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> d >> w;
        hws[d].push_back(w);
    }
    for (int i = 1000; i; i--) {
        for (int w : hws[i]) pq.push(w);
        if (!pq.empty()) {
            ans += pq.top();
            pq.pop();
        }
    }
    cout << ans << '\n';
}