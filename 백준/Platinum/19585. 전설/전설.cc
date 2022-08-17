#include <iostream>
#include <map>
using namespace std;

struct Trie { bool ext = false; map<char, Trie*> next; };

int C, N, Q;
string str;
bool A[2000], B[2000];
Trie *colors, *names;

void insertWord(Trie* cur, int idx, const bool& dir) {
    if (idx >= str.size() || idx < 0) {
        cur->ext = true;
        return;
    }
    char& c = str[idx];
    if (!cur->next[c]) cur->next[c] = new Trie();
    insertWord(cur->next[c], idx + (dir ? -1 : 1), dir);
}

void check(Trie* cur, int idx, const bool& dir, bool arr[]) {
    char& c = str[idx];
    if (idx >= str.size() || idx < 0 || !cur->next[c]) return;
    if (cur->next[c]->ext) arr[idx] = true;
    check(cur->next[c], idx + (dir ? -1 : 1), dir, arr);
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    colors = new Trie();
    names = new Trie();
    
    cin >> C >> N;
    for (int i = 0; i < C; i++) {
        cin >> str;
        insertWord(colors, 0, false);
    }
    for (int i = 0; i < N; i++) {
        cin >> str;
        insertWord(names, str.size() - 1, true);
    }
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        cin >> str;
        fill_n(A, str.size(), false);
        fill_n(B, str.size(), false);
        check(colors, 0, false, A);
        check(names, str.size() - 1, true, B);
        bool pos = false;
        for (int j = 0; j < str.size() - 1; j++) {
            if (A[j] && B[j + 1]) { pos = true; break; }
        }
        cout << (pos ? "Yes" : "No") << '\n';
    }
}