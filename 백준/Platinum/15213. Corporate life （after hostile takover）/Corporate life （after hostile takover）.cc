#include <iostream>
#include <vector>
using namespace std;

int N, a, curIdx;
int tree[200001], cnt[200001];
int order[200001][2];
vector<int> edges[2][200001];

void update(int i) {
    while (i <= N) {
        tree[i]++;
        i += (i & -i);
    }
}

int findSum(int i) {
    int sum = 0;
    while (i) {
        sum += tree[i];
        i -= (i & -i);
    }
    return sum;
}

void setOrder(int i) {
    order[i][0] = ++curIdx;
    for (int e : edges[1][i]) {
        setOrder(e);
    }
    order[i][1] = curIdx;
}

int findRangeSum(int i) {
    return findSum(order[i][1]) - findSum(order[i][0]);
}

void solve(int i) {
    int init = findRangeSum(i);
    for (int e : edges[0][i]) solve(e);
    cnt[i] = findRangeSum(i) - init;
    update(order[i][0]);
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N;
    for (int i = 0; i < 2; i++) {
        for (int j = 2; j <= N; j++) {
            cin >> a;
            edges[i][a].push_back(j);
        }
    }
    
    setOrder(1);
    solve(1);
    for (int i = 1; i <= N; i++) cout << cnt[i] << ' ';
    cout << '\n';
}