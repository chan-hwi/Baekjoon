#include <iostream>
#include <map>
#include <queue>
#include <algorithm>
#define MOD 1234567891LL
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

int T;
ll N, M;
map<ll, ll> ans;
map<pll, ll> cnt;

void swap(ll &a, ll& b) { ll t = a; a = b; b = t; }

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> N >> M;
        if (N > M) swap(N, M);
        queue<pll> q;
        q.push({ N, M });
        cnt[{ N, M }] = 1;

        while (!q.empty()) {
            ll cN = q.front().first, cM = q.front().second;
            ll cur = cnt[q.front()];
            q.pop();

            if (cN == 1) {
                ans[cM] = (ans[cM] + cur) % MOD;
                continue;
            }

            map<pll, ll> curCnt;
            for (const auto& [a, b] : (pll[4]){
                { (cN + 1) / 2, (cM + 1) / 2 },
                { cN / 2, (cM + 1) / 2 }, 
                { (cN + 1) / 2, cM / 2 }, 
                { cN / 2, cM / 2 } }) {
                
                if (a > b) curCnt[{ b, a }] = (curCnt[{ b, a }] + cur) % MOD;
                else curCnt[{ a, b }] = (curCnt[{ a, b }] + cur) % MOD;
            }

            for (auto it = curCnt.rbegin(); it != curCnt.rend(); it++) {
                if (cnt.find(it->first) == cnt.end()) q.push(it->first);
                cnt[it->first] = (cnt[it->first] + it->second) % MOD;
            }
        }

        cout << ans.size() << '\n';
        for (auto& k : ans) {
            cout << k.first << ' ' << k.second << '\n';
        }

        ans.clear();
        cnt.clear();
    }
}