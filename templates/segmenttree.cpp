#include <iostream>

/**
 * Segment tree - easy modification, no lazy propogation
 * Current implementation: summation & updating
 * Credit to max for helping me
 */

using namespace std;

int const MN = 100000;

int n, q;
int arr[MN+5];

struct node {
    int sum;
};

node seg[4*MN+5];

node combine(node x, node y) {
    return {x.sum + y.sum};
}

void update(int node_idx, int update_idx, int left_range, int right_range, int new_value) {
    if (left_range == right_range) seg[node_idx] = {new_value};
    else {
        int partition = (left_range + right_range) >> 1; //[left_range, partition][partition+1, right_range]
        // update children according to where the update index is
        if (update_idx <= partition) update(2 * node_idx, update_idx, left_range, partition, new_value);
        else update(2 * node_idx + 1, update_idx, partition + 1, right_range, new_value);
        // recombine children
        seg[node_idx] = combine(seg[2*node_idx], seg[2*node_idx+1]);
    }
}

node query(int node_idx, int query_left, int query_right, int left_range, int right_range) {
    // case 1: the current range is completely outside of the queried range, return nothing
    if (left_range > query_right || right_range < query_left) return {0};
    // case 2: the current range is completely inside of the queried range, return everything
    else if (left_range >= query_left && right_range <= query_right) return seg[node_idx];
    // case 3: the current range is partially inside, or the queried range is inside the current range, traverse and combine answers
    else {
        int partition = (left_range + right_range) >> 1;
        auto a1 = query(node_idx * 2, query_left, query_right, left_range, partition);
        auto a2 = query(node_idx * 2 + 1, query_left, query_right, partition+1, right_range);
        return combine(a1, a2);
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
        update(1, i, 1, n, arr[i]);
    }
    cin >> q;
    while (q--) {
        int cmd;
        cin >> cmd;
        if (cmd == 1) { // query
            int l, r; cin >> l >> r;
            cout << query(1, l, r, 1, n).sum << '\n';
        } else if (cmd == 2) { // update
            int idx, v; cin >> idx >> v;
            update(1, idx, 1, n, v);
        }
    }
}

// tested on https://dmoj.ca/problem/segtree
