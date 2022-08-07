#include <iostream>
using namespace std;

int N, M, ans;
bool board[100][100];

int getIdx(int i, int j) {
    int ret = -1;
    for (int k = j + 1; k < M; k++) {
        if (board[i][k]) {
            board[i][k] = false;
            ret = k;
        }
    }
    return ret;
}

bool removeOutline() {
    int i = 0, j = 0;
    bool check = false;
    while (i < N) {
        if (board[i][j]) {
            board[i][j] = false;
            check = true;
        }
        int k = getIdx(i, j);
        if (k == -1) i++;
        else {
            j = k;
            check = true;
        }
    }
    return check;
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> board[i][j];
        }
    }

    while (removeOutline()) ans++;
    cout << ans << '\n';
}