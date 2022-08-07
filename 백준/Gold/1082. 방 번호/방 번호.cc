#include <iostream>
using namespace std;

int N, M, t;
int P[10];

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N;
    for (int i = 0; i < N; i++) cin >> P[i];
    cin >> M;

    if (N == 1) {
        cout << 0 << '\n';
        return 0;
    }

    int a = 50;
    for (int i = 1; i < N; i++) a = min(a, P[i]);
    int b = min(a, P[0]);

    for (t = 50; t > 1; t--) if (a + b * (t - 1) <= M) break;
    
    int k = N - 1;
    for (int i = t; i; i--) {
        while (P[k] + (i - 1) * b > M) k--;
        cout << k;
        M -= P[k];
    }
    cout << '\n';
}