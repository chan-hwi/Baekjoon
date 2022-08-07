#include <iostream>
#include <algorithm>
using namespace std;

typedef pair<int, int> pii;

int N, M, a, b, p, sum, ans = -1;
pii sorted[100000];

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> a >> b;
        sorted[i] = { b, -a };
    }
    sort(sorted, sorted + N);
    p = sorted[0].first, sum = -sorted[0].second;
    if (sum >= M) ans = p;
    for (int i = 1; i < N; i++) {
        if (sorted[i].first == sorted[i - 1].first) p += sorted[i].first;
        else p = sorted[i].first;
        sum += -sorted[i].second;
        if (sum >= M && (ans == -1 || ans != -1 && p < ans)) ans = p; 
    }
    cout << ans << '\n';
}