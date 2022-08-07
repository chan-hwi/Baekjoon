#include <iostream>
using namespace std;

int N, a, ans;
bool isAllOne = true;

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> a;
        ans ^= a;
        if (a != 1) isAllOne = false;
    }
    if (isAllOne) cout << (ans ? "cubelover" : "koosaga") << '\n';
    else cout << (ans ? "koosaga" : "cubelover") << '\n';
}