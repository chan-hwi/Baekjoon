#include <iostream>
#define MAX 100000
using namespace std;

typedef long long ll;

int N, a, b;
ll tree[MAX + 2];

void update(int i, int diff) {
    while (i <= MAX) {
        tree[i] += diff;
        i += (i & -i);
    }
}

void updateRange(int i, int j, int diff) {
    update(i, diff);
    update(j + 1, -diff);
}

ll findSum(int i) {
    ll sum = 0;
    while (i) {
        sum += tree[i];
        i -= (i & -i);
    }
    return sum;
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N;
    while (N--) {
        cin >> a >> b;
        ll cur, curSum = 0;
        for (int k : { a, b }) {
            cur = findSum(k);
            updateRange(k, k, -cur);
            curSum += cur;
        }
        if (a + 1 <= b - 1) updateRange(a + 1, b - 1, 1);
        cout << curSum << '\n';
    }
}