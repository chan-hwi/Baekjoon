#include <iostream>
using namespace std;

long long N;
int a[5] = { 0, 1, 0, 1, 2 };

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N;
    cout << (a[N % 5] ? "SK" : "CY") << '\n';
}