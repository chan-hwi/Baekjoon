#include <iostream>
using namespace std;

int T, N, pidx;
int preorder[1000], inorder[1000];

void printPostOrder(int i, int j) {
    int k;
    for (k = i; k <= j; k++) if (inorder[k] == preorder[pidx]) break;
    pidx++;
    if (i <= k - 1) printPostOrder(i, k - 1);
    if (k + 1 <= j) printPostOrder(k + 1, j);
    cout << inorder[k] << ' ';
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> N;
        for (int i = 0; i < N; i++) cin >> preorder[i];
        for (int i = 0; i < N; i++) cin >> inorder[i];
        pidx = 0;
        printPostOrder(0, N - 1);
        cout << '\n';
    }
}