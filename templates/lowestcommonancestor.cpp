#include <iostream>
#include <vector>

#define pii pair<int, int>

using namespace std;

/**
* Using a sparse table to get LCA of
* an undirected unweighted* tree
* in constant time with preprocessing
*
* *note that weighted trees can be supported
* by setting depth(u) to depth(par)+w instead of depth(par)+1
*/

int const LAYERS = 18;
int const MN = 100000;

// euler tour is 2n-1 indices
pii sparse[LAYERS][2 * MN+5]; // {node, depth}
int first[MN+5], vis[MN+5];
int nodes, q;

vector<int> g[MN+5];

int ptr;
void tour(int cur, int depth) {
    first[cur] = ptr;
    sparse[0][ptr++] = {cur, depth};
    vis[cur] = 1;

    for (int const &e : g[cur]) {
        if (!vis[e]) {
            vis[e] = 1;
            tour(e, depth + 1);
            sparse[0][ptr++] = {cur, depth};
        }
    }
}

void build() {
    vis[1] = 1;
    tour(1, 0);

    // dp
    for (int layer = 1; layer < LAYERS; ++layer) {
        for (int i = 0; i + (1 << layer) <= ptr; ++i) {
            auto a1 = sparse[layer-1][i];
            auto a2 = sparse[layer-1][i + (1 << (layer-1))];
            sparse[layer][i] = (a1.second < a2.second) ? a1 : a2;
        }
    }
}

int lca(int u, int v) {
    int l = first[u], r = first[v];
    if (l > r) swap(l, r);

    // find the layer
    int layer = 31 - __builtin_clz(r-l+1);

    auto a1 = sparse[layer][l];
    auto a2 = sparse[layer][r - (1 << layer) + 1];

    // take the minimum of the 2
    return (a1.second < a2.second) ? a1.first : a2.first;
}

int main() {
    // get input
    cin >> nodes >> q;
    for (int i = 1; i < nodes; ++i) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    build();
    for (int i = 1; i <= q; ++i) {
        int u, v; cin >> u >> v;
        cout << lca(u, v) << '\n';
    }
}

/**
Sample Input:
5 4
1 2
1 3
2 4
2 5
4 5
3 4
1 2
2 2

Expected Output:
2
1
1
2
*/