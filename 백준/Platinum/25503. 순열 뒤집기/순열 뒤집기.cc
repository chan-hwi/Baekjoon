#include <iostream>
#include <queue>
using namespace std;

int N, x;
int d[2] = { -1, 1 };
int nums[300001], pr[300001], lvl[300001], l[300001], r[300001], minVal[300001], maxVal[300001];
queue<int> q;

void swap(int &a, int &b) { int t = a; a = b; b = t; }

int Find(int u) { return (u == pr[u] ? u : pr[u] = Find(pr[u])); }

void Union(int u, int v) {
    u = Find(u), v = Find(v);
    if (u == v) return;
    if (lvl[u] > lvl[v]) swap(u, v);
    if (lvl[u] == lvl[v]) lvl[v]++;
    pr[u] = v;
    l[v] = min(l[u], l[v]);
    r[v] = max(r[u], r[v]);
    minVal[v] = min(minVal[u], minVal[v]);
    maxVal[v] = max(maxVal[u], maxVal[v]);
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> nums[i];
        l[i] = r[i] = pr[i] = i;
        minVal[i] = maxVal[i] = nums[i];
        q.push(i);
    }

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        int pc = Find(cur);
        if (l[pc] == 1 && r[pc] == N) {
            cout << "YES" << '\n';
            return 0;
        }
        int arr[2] = { l[pc], r[pc] };
        for (int j = 0; j < 2; j++) {
            int nx = arr[j] + d[j];
            if (nx < 1 || nx > N) continue;
            int pnx = Find(nx);
            if (pnx == pc) continue;
            if (minVal[pnx] == maxVal[pc] + 1 || minVal[pc] == maxVal[pnx] + 1) {
                Union(cur, nx);
                q.push(nx);
            }
        }
    }
    cout << "NO" << '\n';
}