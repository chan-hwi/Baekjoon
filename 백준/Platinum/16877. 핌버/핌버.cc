#include <iostream>
using namespace std;

int N, num, ans;
int p[31], a[3000001];
bool v[15];

int main() {
    int c = 1, b = 1, idx = 0;
    while (b <= 3000000) {
        p[idx++] = b;
        b = c + b;
        c = b - c;
    }
    for (int i = 1; i <= 3000000; i++) {
        fill_n(v, min(i, 15), false);
        for (int j = 0; j < 31; j++) {
            if (i - p[j] >= 0) v[a[i - p[j]]] = true;
        }
        bool pos = true;
        for (int k = 0; k < min(i, 15); k++) {
            if (!v[k]) { a[i] = k; pos = false; break; }
        }
        if (pos) a[i] = min(i, 15);
    }
    cin >> N;
    while (N--) {
        cin >> num;
        ans ^= a[num];
    }
    cout << (ans ? "koosaga" : "cubelover") << '\n';
}