#include <iostream>
#define MOD 9999991
using namespace std;

struct Node {
    int num, cnt = 1;
    Node *l = nullptr, *r = nullptr;
    ~Node() {
        delete l;
        delete r;
    }
};

int T, N, k;
int comb[21][21];

void insertNode(Node *cur, const int& val) {
    cur->cnt++;
    if (cur->num < val) {
        if (!cur->r) {
            cur->r = new Node();
            cur->r->num = val;
            return;
        }
        insertNode(cur->r, val);
    }
    else {
        if (!cur->l) {
            cur->l = new Node();
            cur->l->num = val;
            return;
        }
        insertNode(cur->l, val);
    }
}

int solve(Node *cur) {
    if (!cur) return 1;
    int a = solve(cur->l), b = solve(cur->r);
    int na = (cur->l ? cur->l->cnt : 0);
    int nb = (cur->r ? cur->r->cnt : 0);
    return (long long)comb[na + nb][na] * a % MOD * b % MOD;
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> T;
    for (int i = 0; i <= 20; i++) {
        comb[i][0] = comb[i][i] = 1;
        for (int j = 1; j < i; j++) comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % MOD;
    }
    while (T--) {
        cin >> N;
        cin >> k;
        Node *root = new Node();
        root->num = k;
        for (int i = 1; i < N; i++) {
            cin >> k;
            insertNode(root, k);
        }

        cout << solve(root) << '\n';
        delete root;
    }
}