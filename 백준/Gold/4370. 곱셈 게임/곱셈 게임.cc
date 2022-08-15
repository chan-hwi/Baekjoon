#include <iostream>
#include <map>
using namespace std;

unsigned N;
map<unsigned, bool> dp;

bool solve(unsigned p = 1) {
    if (dp.find(p) != dp.end()) return dp[p];
    for (unsigned i = 2; i <= 9; i++) {
        unsigned a = p * i;
        if (a <= p || a >= N) return true;
        if (!solve(a)) return dp[p] = true;
    }
    return dp[p] = false;
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    while (cin >> N) {
        cout << (solve() ? "Baekjoon wins." : "Donghyuk wins.") << '\n';
        dp.clear();
    }
}