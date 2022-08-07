#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

typedef pair<int, int> pii;

int N, s, t, a, b, c, d, ans;
int months[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
pii dates[100000];
priority_queue<int> pq;

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    for (int i = 1; i <= 12; i++) months[i] += months[i - 1];
    s = months[2] + 1, t = months[10] + 30;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> a >> b >> c >> d;
        dates[i] = { months[a - 1] + b, months[c - 1] + d };
    }
    sort(dates, dates + N);

    int cur = s, j = 0;
    while (cur <= t) {
        while (j < N && dates[j].first <= cur) pq.push(dates[j++].second);
        if (pq.empty() || pq.top() < cur) {
            cout << 0 << '\n';
            return 0;
        }
        cur = pq.top();
        pq.pop();
        ans++;
    }
    cout << ans << '\n';
}