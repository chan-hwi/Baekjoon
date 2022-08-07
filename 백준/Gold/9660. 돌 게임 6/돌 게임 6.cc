#include <iostream>
using namespace std;

long long N;

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N;
    if (N % 7 == 0 || N % 7 == 2) cout << "CY" << '\n';
    else cout << "SK" << '\n';
}