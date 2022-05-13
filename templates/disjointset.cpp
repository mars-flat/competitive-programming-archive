#include <iostream>

using namespace std;

/**
 * Disjoint Set:
 * Path Compression & Union by Size
 * Merges sets, finds size of set
 * in some fast TC that I don't know
 * but its like O(log N) average or smth
 */

int const MN = 100000;

int n, q;
int par[MN+5], sz[MN+5];

// path compression
int getRoot(int u) {
    return par[u] == u ? par[u] : par[u] = getRoot(par[u]);
}

// merge by size
void unite(int u, int v) {
    int uu = getRoot(u), vv = getRoot(v);
    if (uu ^ vv) {
        if (sz[uu] < sz[vv]) swap(uu, vv); // merge vv into uu
        par[vv] = uu;
        sz[uu] += sz[vv];
    }
}

// initialize ds
inline void build() {
    for (int i = 1; i <= n; ++i) {
        par[i] = i;
        sz[i] = 1;
    }
}

int main() {
    cin >> n >> q;
    build();

    // answer queries
    for (int i = 1; i <= q; ++i) {
        int cmd; cin >> cmd;
        if (cmd == 1) { // merge sets
            int u, v; cin >> u >> v;
            unite(u, v);
        } else if (cmd == 2) {
            int x; cin >> x;
            cout << sz[getRoot(x)] << '\n';
        }
    }
}

/**
Sample Input:
5 8
1 1 2
2 2
1 3 4
1 5 2
2 5
2 3
1 2 3
2 1

Expected Output:
2
3
2
5
*/