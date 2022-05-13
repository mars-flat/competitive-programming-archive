#include <iostream>

using namespace std;

/**
 * Binary-Indexed-Tree/Fenwick Tree
 * Range sum queries & updates in O(log N) time
 */

int const MN = 100000;

int bit[MN+5];

int n, q;
int arr[MN+5];

// queries, updates, everything 1-indexed
int qry(int idx) {
    int ret = 0;
    for (int i = idx; i > 0; i -= i & -i) ret += bit[i];
    return ret;
}

// sets the value, not just add
void upd(int idx, int newval) {
    int delta = newval - (qry(idx) - qry(idx-1));
    for (int i = idx; i <= n; i += i & -i) bit[i] += delta;
}

int main() {
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
        // build the structure
        upd(i, arr[i]);
    }

    // answer queries
    for (int i = 1; i <= q; ++i) {
        int cmd; cin >> cmd;
        if (cmd == 1) { // query
            int l, r; cin >> l >> r;
            cout << qry(r) - qry(l-1) << '\n';
        } else if (cmd == 2) { // set
            int idx, val; cin >> idx >> val;
            upd(idx, val);
        }
    }
}

/**
Sample Input:
5 6
1 1 2 3 5
1 1 4
1 2 4
2 2 6
1 2 5
2 3 10
1 3 3

Expected Output:
7
6
16
10
*/