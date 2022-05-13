// author: Shane Chen (MarsFlat)
// concepts: mst, implementation

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <cstring>

#define int long long
#define boost() ios::sync_with_stdio(0); cin.tie(0);
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;

using namespace std;

struct ed {
    int u,v,w,id;
    bool operator < (const ed &o) const {
        if (w == o.w) return id < o.id;
        return w < o.w;
    }
} edges[200005];

unordered_set<int> usedges;

int par[100005], sz[100005];

int getRoot(int x) {
    return par[x] == x ? x : par[x] = getRoot(par[x]);
}

int n, m, d;
int maxcost;
int lastUsed = -1;

signed main() {
    boost(); cin >> n >> m >> d;
    for (int i = 1; i <= n; ++i) {
        par[i] = i; sz[i] = 1;
    }
    for (int i = 1; i <= m; ++i) {
        int u,v,w; cin >> u >> v >> w;
        edges[i] = {u,v,w,i};
    } int used = 0;
    sort(edges+1,edges+m+1);
    for (int i = 1; i <= m; ++i) {
        int uu = getRoot(edges[i].u), uv = getRoot(edges[i].v);
        if (uu != uv) {
            usedges.insert(edges[i].id);
            maxcost = edges[i].w;
            if (sz[uu] < sz[uv]) swap(uu, uv); //uu larger
            par[uv] = uu;
            sz[uu] += sz[uv];
            lastUsed = i;
            if (++used == n-1) break;
        }
    }
    int rem = 0, ext = 0;
    for (int i = 1; i < n; ++i) if (!usedges.count(i)) rem++;
    for (int const &e : usedges) if (e >= n) ext++;
    int days = max(rem, ext);

    // run mst again
    if (edges[lastUsed].id >= n) { // highest new edge
        for (int i = 1; i <= n; ++i) {
            par[i] = i; sz[i] = 1;
        }
        for (int i = 1; i <= m; ++i) {
            int uu = getRoot(edges[i].u), uv = getRoot(edges[i].v);
            if (uu != uv) {
                if (edges[i].w < maxcost || (edges[i].w == maxcost && edges[i].id < n)) {
                    if (sz[uu] < sz[uv]) swap(uu, uv); //uu larger
                    par[uv] = uu;
                    sz[uu] += sz[uv];
                } else if (edges[i].id < n && edges[i].w <= d) return !printf("%lld\n", days-1);
            }
        }
    }
    printf("%lld\n", days);
}
