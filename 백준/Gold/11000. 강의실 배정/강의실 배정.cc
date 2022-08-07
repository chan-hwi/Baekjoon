#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

struct lecture { int s, t; };
bool operator<(lecture& l1, lecture& l2) {
    return (l1.t == l2.t ? l1.s < l2.s : l1.t < l2.t);
}

int N, cs, ct;
map<int, int> curMap;
lecture lectures[200000];


int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> cs >> ct;
        lectures[i] = { cs, ct };
    }
    sort(lectures, lectures + N);
    int j = 0, ans = 0;
    for (int i = 0; i < N; i++) {
        lecture& cur = lectures[i];
        auto lte = curMap.upper_bound(cur.s);
        if (lte == curMap.begin()) {
            curMap[cur.t]++;
            ans++;
        } else {
            lte = prev(lte);
            lte->second--;
            if (!(lte->second)) curMap.erase(lte); 
            curMap[cur.t]++;
        }
    }
    cout << ans << '\n';
}