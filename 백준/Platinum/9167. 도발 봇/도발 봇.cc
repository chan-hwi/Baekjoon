#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

int wordCnt;
bool isFirst, isThg;
string dialog, thg = "theholygrail";
int state[15], cnt[15] = { 4, 3, 1, 2, 2, 1, 1, 3, 5, 11, 2, 2, 1, 7, 5 };
vector<vector<int>> insts[7] = {
    { { 1 }, { 0, 1 }, { 9 }, { 1 } },
    { { 6, 2 }, { 5, 2 }, { 6, 12, 9 } },
    { { 12, 3 } },
    { { 9 }, { 4, 9 } },
    { { 13 }, { 14, 13 } },
    { { 7, 10 } },
    { { 8, 11 } }
};

vector<string> words[8] = {
    { "steed", "king", "first-born" },
    { "mother", "father", "grandmother", "grandfather", "godfather" },
    { "hamster", "coconut", "duck", "herring", "newt", "peril", "chicken", "vole", "parrot", "mouse", "twit" },
    { "is", "masquerades as" },
    { "was", "personified" },
    { "a" },
    { "silly", "wicked", "sordid", "naughty", "repulsive", "malodorous", "ill-tempered" },
    { "conspicuously", "categorically", "positively", "cruelly", "incontrovertibly" }
};

void printStr(const string& str) {
    if (!isFirst) cout << str;
    else {
        cout << (char)(str[0] - 32);
        cout << (string)(&str[0] + 1);
        isFirst = false;
    }
}

void doTaunt(int i = 0) {
    if (!i) isFirst = true;
    int cs = state[i]++;
    state[i] %= cnt[i];
    if (i >= 7) {
        printStr(words[i - 7][cs]);
        return;
    }
    if (i >= 5) printStr("your ");
    for (int k = 0; k < insts[i][cs].size(); k++) {
        doTaunt(insts[i][cs][k]);
        if (k != insts[i][cs].size() - 1) cout << ' ';
    }
    if (!i) {
        isFirst = true;
        cout << (cs == 2 ? '!' : '.');
        wordCnt--;
    }
}

string editDialog(const string& str) {
    wordCnt = 0;
    string cw, ret = "";
    stringstream ss(str);
    while (ss >> cw) {
        for (char c : cw) {
            if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
                wordCnt++;
                break;
            }
        }

        ret += cw;
        ret += (char)32;
    }
    ret.pop_back();

    isThg = false;
    int idx = 0;
    for (int i = 0; i < ret.size(); i++) {
        if (idx >= 12) break;
        if (ret[i] == thg[idx] || ret[i] == thg[idx] - 32) idx++;
    }
    if (idx >= 12) isThg = true;
    return ret;
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    while (getline(cin, dialog, '\n')) {
        dialog = editDialog(dialog);
        cout << "Knight: " << dialog << '\n';

        wordCnt = (wordCnt + 2) / 3;
        if (isThg) {
            cout << "Taunter: (A childish hand gesture)." << '\n';
            wordCnt--;
        }
        while (wordCnt > 0) {
            cout << "Taunter: ";
            doTaunt();
            cout << '\n';
        }
        cout << '\n';
    }
}