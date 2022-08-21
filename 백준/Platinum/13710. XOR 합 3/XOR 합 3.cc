#include <iostream>
using namespace std;

typedef long long ll;

int N, num, i;
ll ans;
int bitCnt[30];

void bitXor(const int& k) {
    int j = 29;
    while (j >= 0) {
        if (k & (1 << j)) bitCnt[j] = i - bitCnt[j];
        ans += (ll)(1 << j) * bitCnt[j];
        j--;
    }
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N;
    for (i = 1; i <= N; i++) {
        cin >> num;
        bitXor(num);
    }
    cout << ans << '\n';
}