#include <iostream>
using namespace std;

int N;
int g[1001];
bool v[1001];

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N;
    for (int i = 2; i <= N; i++) {
        fill_n(v, i + 1, false);
        for (int j = 0; j <= i - 2 - j; j++) {
            v[g[j] ^ g[i - 2 - j]] = true;
        }
        int k;
        for (k = 0; k < i; k++) if (!v[k]) break;
        g[i] = k;
    }
    cout << (g[N] ? 1 : 2) << '\n';
}