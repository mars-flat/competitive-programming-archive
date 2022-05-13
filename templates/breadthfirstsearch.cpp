#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/**
 * Breadth-First Search (BFS)
 * Example uses shortest path
 * on an undirected unweighted graph
 * to each node from node 1
 */

int const MN = 100000;

// adjacency matrix: stores graph
vector<int> g[MN+5];
int nodes, edges;
int vis[MN+5];

// queue structure to perform BFS
queue<int> bfs;

int main() {
    // get input
    cin >> nodes >> edges;
    for (int i = 1; i <= edges; ++i) {
        int from, to; cin >> from >> to;
        g[from].push_back(to);
        g[to].push_back(from);
    }
    // push starting node into queue
    bfs.push(1);
    vis[1] = 1;
    while (!bfs.empty()) {
        int nxt = bfs.front(); bfs.pop();
        // iterate over all neighbours
        for (int const &e : g[nxt]) {
            if (!vis[e]) {
                vis[e] = vis[nxt]+1; // unweighted, add 1
                bfs.push(e);
            }
        }
    }
    // output, -1 if unreachable
    for (int i = 1; i <= nodes; ++i) {
        cout << (vis[i] == 0 ? -1 : vis[i]-1) << " \n"[i == nodes];
    }
}

/**
Sample input:
6 8
1 3
1 4
1 5
1 4
1 5
2 3
2 4
4 5

Expected Output:
0 2 1 1 1 -1
*/