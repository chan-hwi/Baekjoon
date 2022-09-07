#include <iostream>
#include <map>
using namespace std;

struct Node {
    int cnt = 0;
    bool end = false, pd = false;
    map<char, Node*> next;
    ~Node() {
        for (auto it : next) {
            delete it.second;
        }
    }
};

int T, N, ans;
string str;
Node* root;

void insertNode(Node* cur, int idx, bool pd) {
    if (pd) cur->pd = true;
    else cur->cnt++;
    if (idx >= str.size()) {
        if (!cur->pd) cur->end = true;
        return;
    }
    if (cur->next.find(str[idx]) == cur->next.end()) cur->next[str[idx]] = new Node();
    insertNode(cur->next[str[idx]], idx + 1, pd);
}

void dfs(Node* cur) {
    if (!cur->cnt) return;
    if (!cur->pd) {
        ans++;
        return;
    }
    if (cur->end) ans++;
    for (auto& it : cur->next) {
        dfs(it.second);
    }
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        root = new Node();
        ans = 0;
        cin >> N;
        for (int i = 0; i < N; i++) {
            cin >> str;
            insertNode(root, 0, false);
        }

        cin >> N;
        for (int i = 0; i < N; i++) {
            cin >> str;
            insertNode(root, 0, true);
        }

        dfs(root);
        cout << ans << '\n';
        delete root;
    }
}