#include <iostream>
#include <vector>
#define MAX 1048576
using namespace std;

int N, M, K, a, b, cd;
int nums[MAX + 1], win[MAX + 1], cnt[MAX + 1], lvl[MAX + 1];
vector<int> v;
vector<int> edges[MAX + 1];

void swap(int &u, int &v) { int t = u; u = v; v = t; }

bool solve(int i) {
    if (edges[i].empty()) return true;
    cd++;
    for (int e : edges[i]) {
        if (!solve(e)) return false;
    }
    cd--;
    int bm = 0;
    for (int e : edges[i]) {
        if (bm & (1 << lvl[e])) {
            vector<int> ans;
            for (int f : edges[i]) if (lvl[f] == lvl[e]) ans.push_back(f);
            cout << min(ans[0], ans[1]) << ' ' << v[1] << '\n';
            cout << max(ans[0], ans[1]) << ' ' << v[1] << '\n';
            return false;
        }
        bm |= (1 << lvl[e]);
    }
    int j = 0;
    while (bm & (1 << j)) j++;
    if (bm > (1 << j)) {
        cout << i << ' ' << v[1] << '\n';
        return false;
    }
    lvl[i] = j;
    return true;
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N;
    M = 1 << N;
    K = M - 2;
    while (K--) {
        cin >> a >> b;
        win[b] = a;
        edges[a].push_back(b);
        cnt[a]++;
    }
    
    for (int i = 1; i <= M; i++) {
        if (!win[i]) v.push_back(i);
    }
    if (cnt[v[0]] == cnt[v[1]]) {
        cout << min(v[0], v[1]) << ' ' << max(v[0], v[1]) << '\n';
        cout << max(v[0], v[1]) << ' ' << min(v[0], v[1]) << '\n';
        return 0;
    }
    if (cnt[v[0]] < cnt[v[1]]) swap(v[0], v[1]);

    solve(v[0]);
}