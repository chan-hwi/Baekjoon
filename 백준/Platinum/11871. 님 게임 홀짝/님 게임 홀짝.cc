#include <iostream>
using namespace std;

int N, a, ans;

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> a;
        a = (a % 2 ? (a + 1) >> 1 : (a >> 1) - 1);
        ans ^= a;
    }
    cout << (ans ? "koosaga" : "cubelover") << '\n';
}