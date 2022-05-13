#include <iostream>
#include <vector>
#include <queue>

#define pii pair<int, int>

using namespace std;

/**
 * Dijkstra's SSSP algorithm
 * Shortest path from node 1 to all nodes
 * on undirected, weighted graph
 */

int const MN = 100000;
int const INF = INT32_MAX;

vector<pii> g[MN+5];

int nodes, edges;

int vis[MN+5], dis[MN+5];

// {dist, node}
priority_queue<pii, vector<pii>, greater<pii>> dijk;

int main() {
    // get input
    cin >> nodes >> edges;
    for (int i = 1; i <= edges; ++i) {
        int u, v, w; cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    // initialize dists to INF
    fill(dis, dis+nodes+5, INF);

    dis[1] = 0;
    // start by pushing 1
    dijk.push({0, 1});

    // let propogate
    while (!dijk.empty()) {
        pii nxt = dijk.top();
        dijk.pop();
        int dist = nxt.first, node = nxt.second;

        // important line, make sure dist is optimal already
        if (dist != dis[node]) continue;

        for (pii const &p : g[node]) {
            int onode = p.first, w = p.second;
            if (!vis[onode] && w + dist < dis[onode]) {
                dis[onode]= w + dist;
                dijk.push({dis[onode], onode});
            }
        }

        // make sure to set vis at post-traversal
        vis[node]=1;
    }
    for (int i = 1; i <= nodes; ++i) {
        cout << (dis[i] == INF ? -1 : dis[i]) << " \n"[i == nodes];
    }
}

/**
Sample Input:
4 3
1 2 2
1 3 5
2 3 2

Expected Output:
0 2 4 -1
 */
