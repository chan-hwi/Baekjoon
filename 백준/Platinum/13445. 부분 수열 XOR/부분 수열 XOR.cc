#include <iostream>
using namespace std;

typedef long long ll;

ll ans;
int N, K, num, xorVal;
int tree[400005];

void update(const int& val, int n = 1, int d = 16) {
    tree[n]++;
    if (d < 0) return;
    if (val & (1 << d)) update(val, n * 2 + 1, d - 1);
    else update(val, n * 2, d - 1);
}

int findCnt(const int& val, int n = 1, int d = 16) {
    if (d < 0 || !tree[n]) return 0;
    if (K & (1 << d)) 
        return ((val & (1 << d)) ? 
                tree[n * 2 + 1] + findCnt(val, n * 2, d - 1) :
                tree[n * 2] + findCnt(val, n * 2 + 1, d - 1));
    return findCnt(val, n * 2 + ((val & (1 << d)) != 0), d - 1);
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N >> K;
    if (K >= (1 << 17)) {
        cout << (ll)N * (N + 1) / 2 << '\n';
        return 0;
    }
    update(0);
    for (int i = 0; i < N; i++) {
        cin >> num;
        xorVal ^= num;
        ans += findCnt(xorVal);
        update(xorVal);
    }

    cout << ans << '\n';
}