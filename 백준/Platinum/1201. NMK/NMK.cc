#include <iostream>
using namespace std;

int N, M, K, idx;
int ans[500];
bool rev;

void swap(int& a, int& b) { int t = a; a = b; b = t; }

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N >> M >> K;
    if (N < M + K - 1 || N > M * K) {
        cout << -1 << '\n';
        return 0;
    }

    if (M < K) {
        swap(M, K);
        rev = true;
    }
    int rem = N;
    for (int i = M - 1; i >= 0; i--) {
        int cnt = min(K, rem - i);
        for (int j = rem - cnt + 1; j <= rem; j++) ans[idx++] = j;
        rem -= cnt;
    }
    if (rev) for (int i = 0; i < N; i++) cout << ans[i] << ' ';
    else for (int i = N - 1; i >= 0; i--) cout << ans[i] << ' ';
    cout << '\n';
}