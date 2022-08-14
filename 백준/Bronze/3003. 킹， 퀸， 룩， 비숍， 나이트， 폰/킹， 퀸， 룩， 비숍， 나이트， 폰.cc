#include <iostream>
using namespace std;

int a;
int nums[6] = { 1, 1, 2, 2, 2, 8 };

int main() {
    cin.tie(NULL);    ios_base::sync_with_stdio(false);
    for (int i=0; i < 6; i++) {
        cin >> a;
        cout << nums[i] - a << ' ';
    }
    cout << '\n';
}