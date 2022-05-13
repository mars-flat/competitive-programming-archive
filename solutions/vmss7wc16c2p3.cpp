// author: Shane Chen
// concepts: dp, lis

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
int pos[1000005], dp[1000005];

int main() {
    boost(); cin >> n;
    memset(dp, 0x3f, sizeof dp);
    dp[0] = -1;
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        pos[x] = i;
    }
    cin >> m;
    int sz = 0;
    for (int i = 1; i <= m; ++i) {
        int x; cin >> x;
        x = pos[x];
        if (x == 0) continue;
        int lo = 1, hi = 1000001;
        int candidate = -1;
        while (lo < hi) {
            int mid = (lo+hi)>>1;
            if (dp[mid] < x) { // cant update, go higher
                lo = mid+1;
            } else { // can update
                if (dp[mid-1] < x) candidate = mid;
                hi = mid;
            }
        }
        if (candidate != -1) {
            dp[candidate] = x;
            sz = max(sz, candidate);
        }
    }
    cout << sz << '\n';
}
