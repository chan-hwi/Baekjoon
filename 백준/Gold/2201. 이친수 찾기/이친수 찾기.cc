#include <iostream>
using namespace std;

typedef long long ll;

ll k;
ll pibo[88];
string ans;

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    pibo[0] = pibo[1] = 1;
    for (int i = 2; i < 88; i++) {
        pibo[i] = pibo[i - 1] + pibo[i - 2];
    }
    cin >> k;
    k++;
    int idx = 1;
    while (pibo[idx] < k) idx++;
    idx--;
    
    while (idx) {
        if (pibo[idx] < k) {
            ans += '1';
            k -= pibo[idx];
        } else ans += '0';
        idx--;
    }
    cout << ans << '\n';
}