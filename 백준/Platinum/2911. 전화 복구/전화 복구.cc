#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

typedef pair<int, int> pii;

int N, M, u, v;
long long ans;
map<int, int> m;
pii nodes[100000];

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    m[1] = 0;
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> u >> v;
        nodes[i] = { v, u + 1 };
    }
    sort(nodes, nodes + N);
    
    int idx = 0;
    while (idx < N) {
        int c = idx;
        auto ci = m.lower_bound(nodes[idx].second);
        while (idx < N - 1 && nodes[idx].first == nodes[idx + 1].first && m.lower_bound(nodes[idx + 1].second) == ci) idx++;
        ans += nodes[idx].first - ci->second;
        ci->second = nodes[idx].first;
        for (int k = c; k <= idx; k++) {
            m[nodes[k].second] = nodes[k].first;
        }
        idx++;
    }
    cout << ans << '\n';
}