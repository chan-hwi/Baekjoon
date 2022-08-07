#include <iostream>
#define MOD 1000000007
using namespace std;

typedef long long ll;

int N;
ll cur = 1;

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N;
    for (int i = 2; i <= N; i++) cur = cur * i % MOD * i % MOD;
    ll k = (ll)N * (N + 1) / 2 % MOD;
    ll maxVal = ((ll)N * (N + 1) * (N * 2 + 1) / 6 % MOD + k * k % MOD) % MOD;
    cout << maxVal << ' ' << cur << '\n';
}