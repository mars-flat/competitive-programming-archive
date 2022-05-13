#include <iostream>

using namespace std;

/**
 * Sparse table implementation
 * Range Minimum Query in O(1)
 */

int const LAYERS = 20;
int const MN = 1000000;

int n, q;
int a[MN+5], sparse[LAYERS][MN+5];

void build() {
    for (int i = 0; i < n; ++i) sparse[0][i] = a[i];
    for (int layer = 1; layer < LAYERS; ++layer) {
        for (int i = 0; i + (1 << layer) <= n; ++i) {
            sparse[layer][i] = min(sparse[layer-1][i], sparse[layer-1][i + (1 << (layer - 1))]);
        }
    }
}

// query inclusive range, 0-indexed
int query(int l, int r) {
    int layer = 31 - __builtin_clz(r-l+1);
    return min(sparse[layer][l], sparse[layer][r - (1 << layer) + 1]);
}

int main() {
    cin >> n >> q;
    for (int i = 0; i < n; ++i) cin >> a[i];

    // build
    build();

    // answer queries
    for (int i = 0; i < q; ++i) {
        int l, r; cin >> l >> r;
        cout << query(l, r) << '\n';
    }
}

/**
Sample Input:
6 5
1 4 2 5 3 2
1 2
3 4
0 5
0 2
1 5

Expected Output:
2
3
1
1
2
*/