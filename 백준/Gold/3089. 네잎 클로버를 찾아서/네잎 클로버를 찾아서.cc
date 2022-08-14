#include <iostream>
#include <algorithm>
#define ADD 99999
using namespace std;

typedef pair<int, int> pii;

struct Node {
    int y, x;
    Node* dir[4] = { nullptr, };
    Node(int y, int x) : y(y), x(x) {}
};

int N, M, a, b;
string moves;
pii poses[100000];
Node* cur;
Node* closest[4], *xpos[200000];

int moveToIdx(char& c) {
    if (c == 'L') return 0;
    if (c == 'R') return 1;
    if (c == 'D') return 2;
    if (c == 'U') return 3;
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> a >> b;
        poses[i] = { b, a };
    }
    cin >> moves;
    sort(poses, poses + N);
    Node* pn = nullptr;
    for (int i = 0; i < N; i++) {
        Node* nn = new Node(poses[i].first, poses[i].second);
        if (!nn->y) {
            if (nn->x <= 0 && (!closest[0] || closest[0]->x < nn->x)) closest[0] = nn;
            if (nn->x >= 0 && (!closest[1] || closest[1]->x > nn->x)) closest[1] = nn;
        }
        if (!nn->x) {
            if (nn->y <= 0 && (!closest[2] || closest[2]->y < nn->y)) closest[2] = nn;
            if (nn->y >= 0 && (!closest[3] || closest[3]->y > nn->y)) closest[3] = nn;
        }
        if (i && pn->y == nn->y) {
            pn->dir[1] = nn;
            nn->dir[0] = pn;
        }
        if (xpos[nn->x + ADD]) {
            Node* bn = xpos[nn->x + ADD];
            bn->dir[3] = nn;
            nn->dir[2] = bn;
        }
        xpos[nn->x + ADD] = nn;
        pn = nn;
    }

    cur = closest[moveToIdx(moves[0])];
    for (int i = cur->y || cur->x; i < M; i++) {
        cur = cur->dir[moveToIdx(moves[i])];
    }
    cout << cur->x << ' ' << cur->y << '\n';
}