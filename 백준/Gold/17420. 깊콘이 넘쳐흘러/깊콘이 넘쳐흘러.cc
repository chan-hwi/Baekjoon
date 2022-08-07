#include <iostream>
#include <vector>
#include <map>
#define AMT 30
using namespace std;

int N, lo;
int A[100000], B[100000];
map<int, vector<int>> sorted;
long long ans;

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N;
    for (int i = 0; i < N; i++) cin >> A[i];
    for (int i = 0; i < N; i++) cin >> B[i];
    for (int i = 0; i < N; i++) sorted[B[i]].push_back(A[i]);

    for (auto& cur : sorted) {
        int maxVal = 0;
        for (int a : cur.second) {
            int k = max(0, max(lo, cur.first) - a + AMT - 1) / AMT;
            maxVal = max(maxVal, a + k * AMT);
            ans += k;
        }
        lo = maxVal;
    }
    cout << ans << '\n';
}