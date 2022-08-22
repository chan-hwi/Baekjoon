#include <iostream>
using namespace std;

int T, a, b, c;
// int df[3][3] = { { -1, -1, 0 }, { -1, 0, -1 }, { 0, -1, -1 } };
// int dp[501][501][501];

void swap(int& a, int& b) { int t = a; a = b; b = t; }

void sv(int& a, int& b, int& c) {
    if (a > b) swap(a, b);
    if (b > c) swap(b, c);
    if (a > b) swap(a, b);
}

// int solve(int a, int b, int c) {
//     sv(a, b, c);
//     if (!a && !b) return 1;
//     int& ret = dp[a][b][c];
//     if (ret != -1) return ret;

//     int tmp[3], arr[3] = { a, b, c };
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 3; j++) {
//             tmp[j] = arr[j] + df[i][j];
//         }
//         sv(tmp[0], tmp[1], tmp[2]);
//         if (tmp[0] < 0) continue;
//         if (!solve(tmp[0], tmp[1], tmp[2])) return ret = 1;
//     }
//     return ret = 0;
// }

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    // fill(&dp[0][0][0], &dp[100][100][101], -1);
    // for (int i = 0; i <= 100; i++) {
    //     cout << "i : " << i << '\n';
    //     for (int j = i; j <= 100; j++) {
    //         for (int k = 0; k < j; k++) cout << "  ";
    //         for (int k = j; k <= 100; k++) {
    //             // cout << i << ", " << j << ", " << k << " : " << solve(i, j, k) << '\n';
    //             cout << solve(i, j, k) << ' ';
    //         }
    //         cout << '\n';
    //     }
    //     cout << '\n';
    // }

    cin >> T;
    while (T--) {
        cin >> a >> b >> c;
        sv(a, b, c);
        if (a == 1 && b == c && (b + c - 2) % 4 == 0) cout << 'B' << '\n';
        else if (a % 2) {
            int col = c + b, dist = c - b;
            if (dist % 2) cout << 'R' << '\n';
            else {
                if ((col + (a - 1) % 4) % 4 == 2 && (dist >> 1) <= (a >> 1) - 1) cout << 'B' << '\n';
                else cout << 'R' << '\n';
            }
        } else {
            int col = c - b + 1;
            bool ans = (b % 2) ^ (col < a && (a % 4 ? col % 4 == 0 : (col + 2) % 4 == 0));
            cout << (ans ? 'R' : 'B') << '\n';
        }
    }
}