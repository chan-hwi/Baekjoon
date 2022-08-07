#include <iostream>
#include <algorithm>
using namespace std;

typedef pair<int, int> pii;

int N, Q, a, b;
pii sl[300000], sr[300000];

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> a >> b;
        sl[i] = { a, b };
        sr[i] = { -b, -a };
    }
    sort(sl, sl + N);
    sort(sr, sr + N);

    cin >> Q;
    while (Q--) {
        cin >> a >> b;
        int lo = lower_bound(sl, sl + N, make_pair(a, b)) - sl;
        if (lo == N || sl[lo].first != a) { cout << -1 << '\n'; continue; }
        if (sl[lo].second == b) { cout << 1 << '\n'; continue; }
        lo = lower_bound(sr, sr + N, make_pair(-b, -a)) - sr;
        if (lo == N || sr[lo].first != -b) { cout << -1 << '\n'; continue; }
        cout << 2 << '\n';
    }
}