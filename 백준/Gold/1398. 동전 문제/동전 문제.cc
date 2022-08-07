#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

int T;
ll num;
int minVal[100];

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    for (int i = 0; i < 100; i++) {
        minVal[i] = i;
        int num = i, j = 0;
        while (true) {
            minVal[i] = min(minVal[i], num / 10 + num % 10 + j);
            if (num < 25) break;
            num -= 25;
            j++;
        }
    }
    cin >> T;
    while (T--) {
        cin >> num;
        ll ans = 0;
        while (num) {
            ans += minVal[num % 100];
            num /= 100;
        }
        cout << ans << '\n';
    }
}