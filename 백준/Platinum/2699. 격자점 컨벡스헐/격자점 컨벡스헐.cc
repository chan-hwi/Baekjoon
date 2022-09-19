#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct pos {
    int x, y;
    bool operator<(pos p) {
        return y == p.y ? x < p.x : y > p.y;
    }
};

int T, N;

int getCross(const pos& p1, const pos& p2, const pos& p3) {
    int x1 = p2.x - p1.x, x2 = p3.x - p1.x;
    int y1 = p2.y - p1.y, y2 = p3.y - p1.y;
    return x1 * y2 - x2 * y1;
}

int main() {
    cin.tie(NULL);  ios_base::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> N;
        vector<pos> poses(N);
        for (int i = 0; i < N; i++) {
            auto& [x, y] = poses[i];
            cin >> x >> y;
        }

        sort(poses.begin(), poses.end());

        vector<pos> left, right;
        left.push_back(poses[0]);
        right.push_back(poses[0]);
        
        for (int i = 1; i < N; i++) {
            pos& p = poses[i];
            while (left.size() >= 2 && getCross(left[left.size() - 2], left.back(), p) <= 0) left.pop_back();
            while (right.size() >= 2 && getCross(right[right.size() - 2], right.back(), p) >= 0) right.pop_back();
            left.push_back(p);
            right.push_back(p);
        }

        if (left.size() >= 3) right.insert(right.end(), left.rbegin() + 1, left.rend() - 1);

        cout << right.size() << '\n';
        for (auto& pos : right) cout << pos.x << ' ' << pos.y << '\n';
    }
}