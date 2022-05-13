// author: MarsFlat
// concepts: 2-d BIT

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <cstring>

// #define int long long
#define boost() ios::sync_with_stdio(0); cin.tie(0);
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;

using namespace std;

int n, k;
long long sm;
int a[3003][3003], bit[3003][3003];

inline void upd(int r, int c, int v) {
    for (int i = r; i <= n; i += i & -i) {
        for (int j = c; j <= n; j += j & -j) {
            bit[i][j] = max(bit[i][j], v);
        }
    }
}

inline int qry(int r, int c) {
    int ret = 0;
    for (int i = r; i > 0; i -= i & -i) {
        for (int j = c; j > 0; j -= j & -j) {
            ret = max(bit[i][j], ret);
        }
    }
    return ret;
}

int main() {
    scan(n); scan(k);
    for (int i = 1; i <= n; ++i) {
        for (int j = n - i + 1; j <= n; ++j) { // 4
            scan(a[i][j]);
        }
    }


    for (int i = n, sz = k; i >= n - k + 1; --i, --sz) {
        for (int j = n - sz + 1; j <= n; ++j) {
            //cout << i << ' ' << j << '\n';
            upd(i,j,a[i][j]);
            sm = max(sm, (long long) a[i][j]);
        }
    }

    /**

     we update in a particular fashion
     0 0 0 3
     0 0 1 2
     0 4 2 1
     6 1 4 2

     0 0 0 0
     0 0 0 *
     0 0 * 1
     0 * 4 2

     update stars

     */

    for (int i = n - k; i > 0; --i) {
        int cr = n, cc = i, fills = 0;
        while (cc <= n) {
            upd(cr, cc, a[cr][cc]); fills++;
            if (fills >= k) {
                int v = qry(cr+(k-1), cc);
                sm += v;
            }
            cr--; cc++;
        }
    }
    cout << sm << '\n';
}
