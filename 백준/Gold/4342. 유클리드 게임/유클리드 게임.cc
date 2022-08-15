#include <iostream>
using namespace std;

int a, b;

void swap(int& u, int& v) { int t = u; u = v; v = t; }

bool gcd(int u, int v) {
    if (u > v) swap(u, v);
    if (!u) return true;
    if (v / u > 1) return false;
    return !gcd(v % u, u);
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    while (true) {
        cin >> a >> b;
        if (!a && !b) break;
        cout << (gcd(a, b) ? "B wins" : "A wins") << '\n';
    }
}