#include <iostream>
#include <algorithm>
using namespace std;

int l, r, i, j;
string A, B, ans;
bool t;

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> A >> B;
    ans.resize(A.size());
    j = r = A.size() - 1;
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    while (l <= r) {
        bool b = A[i] < B[j];
        char c = t ? B[j] : A[i];
        if (!b) {
            int n = (r - l + 2) >> 1;
            c = t ? B[j - n + 1] : A[i + n - 1];
        }
        ans[b ? l++ : r--] = c;
        if (b) {
            if (t) j--;
            else i++;
        }
        t = !t;
    }
    cout << ans << '\n';
}