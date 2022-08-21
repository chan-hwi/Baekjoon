#include <iostream>
#include <cmath>
#include <algorithm>
#define MAX 131072
using namespace std;

typedef long long ll;

int N, M, k;
int nums[MAX + 1], tree[MAX + 1], sorted[MAX + 1];

bool cmp(int i, int j) { return (nums[i] == nums[j] ? i > j : nums[i] < nums[j]); }

void update(int i) {
    while (i <= M) {
        tree[i]++;
        i += (i & -i);
    }
}

int findSum(int i) {
    int cnt = 0;
    while (i) {
        cnt += tree[i];
        i -= (i & -i);
    }
    return cnt;
}

ll getPairCnt() {
    fill_n(tree, M + 1, 0);
    sort(sorted, sorted + M, cmp);
    ll cnt = 0;
    for (int i = 0; i < M; i++) {
        int j = sorted[i];
        cnt += findSum(j + 1);
        update(j + 1);
    }
    return cnt;
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N >> M;
    k = log2(N);
    for (int i = 0; i < M; i++) cin >> nums[i];
    for (int i = 0; i < M; i++) sorted[i] = i;

    ll pv = getPairCnt();
    while (k >= 0) {
        for (int i = 0; i < M; i++) nums[i] ^= (1 << k);
        ll nv = getPairCnt();
        if (pv > nv) for (int i = 0; i < M; i++) nums[i] ^= (1 << k);
        else pv = nv;
        k--;
    }
    cout << pv << '\n';
}