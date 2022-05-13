// author: Shane Chen
// concepts: line sweep, bit

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <bitset>
#include <queue>
#include <cstring>
#include <cassert>

// #define int long long
#define pii pair<int, int>
#define boost() ios::sync_with_stdio(0); cin.tie(0);
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;

using namespace std;

int n, m;

struct thing {
    int y, lo, hi, type; // priority: bottom edges (1), boxlings (2), top edges (3)
    bool operator < (thing const &o) const {
        if (y == o.y) {
            return type < o.type;
        } else return y < o.y;
    }
};

vector<thing> events;
set<int> xe;
vector<int> tmp;
map<int, int> pos;

int bit[600005];

void upd(int idx, int val) {
    for (int i = idx; i <= 600000; i += i & -i) bit[i] += val;
}

int qry(int idx) {
    int ret = 0;
    for (int i = idx; i > 0; i -= i & -i) ret += bit[i];
    return ret;
}

int main() {
    boost(); cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        events.push_back({b, a, c, 1});
        events.push_back({d, a, c, 3});
        xe.insert(a);
        xe.insert(c);
    }
    for (int i = 1; i <= m; ++i) {
        int a, b; cin >> a >> b;
        events.push_back({b, a, a, 2});
        xe.insert(a);
    }
    sort(events.begin(), events.end());
    for (int const &e : xe) tmp.push_back(e);
    for (int i = 1; i <= tmp.size(); ++i) {
        //cout << tmp[i-1] << ' ' << i << '\n';
        pos[tmp[i-1]] = i;
    }

    int ans = 0;

    for (auto const &e : events) {
        //cout << e.y << ' ' << e.lo << ' ' << e.hi << ' ' << e.type << '\n';
        //cout << pos[e.lo] << ' ' << pos[e.hi] << '\n';
        if (e.type == 1) { // add 'edge'
            upd(pos[e.lo], 1);
            upd(pos[e.hi]+1, -1);
        } else if (e.type == 3) { // remove 'edge'
            upd(pos[e.lo], -1);
            upd(pos[e.hi]+1, 1);
        } else if (e.type == 2) { // query
            ans += (qry(pos[e.hi]) > 0) ? 1 : 0;
        }
        //cout << e.y << ' ' << e.lo << ' ' << e.hi << ' ' << e.type << '\n';
    }
    cout << ans << '\n';
}
