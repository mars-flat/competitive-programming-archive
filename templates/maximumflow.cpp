#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

/**
 * Edmonds-Karp Max Flow
 * Max Flow algorithm,
 * node 1 = source
 * node n = sink
 */

int const MN = 500;

unordered_map<int, int> g[MN+5];

int nodes, edges, source, sink;
int vis[MN+5], path[MN+5];
queue<int> buffer;

// find an augmenting path
bool bfs() {
    memset(vis, 0, sizeof vis);
    vis[1] = 1;

    // store the augmenting path
    path[1] = -1;
    buffer.push(1);

    // run bfs
    while (!buffer.empty()) {
        int nxt = buffer.front();
        buffer.pop();
        for (auto const &p : g[nxt]) {

            // make sure you can still add flow
            if (!vis[p.first] && p.second > 0) {
                path[p.first] = nxt;
                vis[p.first] = 1;
                buffer.push(p.first);
            }
        }
    }

    // if sink is not hit, there is
    // no augmenting path
    return vis[sink];
}

int maxflow() {
    int maxflow = 0;
    while (bfs()) {
        int bottleneck = INT32_MAX;

        // get bottleneck
        for (int to = sink; to != source; to = path[to]) {
            int from = path[to];
            bottleneck = min(bottleneck, g[from][to]);
        }
        for (int to = sink; to != source; to = path[to]) {
            int from = path[to];

            // update (subtract) bottleneck value
            // from actual edge
            g[from][to] -= bottleneck;

            // update (add) bottleneck value
            // from residual edge
            g[to][from] += bottleneck;
        }
        // adding the bottleneck (because it's how much you added to the flow)
        // to the final answer
        maxflow += bottleneck;
    }
    return maxflow;
}

int main() {
    cin >> nodes >> edges;
    source = 1;
    sink = nodes;

    for (int i = 1; i <= edges; ++i) {
        int u, v, cap; cin >> u >> v >> cap;
        g[u][v] = cap;
    }

    cout << maxflow() << '\n';
}

/**
Sample Input:
6 9
1 2 16
1 3 13
3 2 4
2 4 12
3 5 14
4 3 9
5 4 7
4 6 20
5 6 4

Expected Output:
23

More resources:
https://jamieheller.github.io/editor.html
*/