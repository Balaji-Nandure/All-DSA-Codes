/**
 * Problem: Find Bridges in a Graph (Critical Connections / Tarjan's Algorithm)
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Simple cycle detection determines whether any cycle exists.
 * - A bridge (cut-edge) is an edge whose removal increases the number of connected components.
 * - Tarjan's algorithm finds ALL bridges in a single DFS pass using discovery times and low-link values.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - DFS Tree Low-Link Values (Tarjan's Bridge Theorem):
 *   - `disc[u]`: Timestamp when vertex `u` is first visited during DFS.
 *   - `low[u]`: Lowest `disc` reachable from `u` using at most one back-edge.
 *   - For each neighbor `v` of `u` (with parent `p`):
 *     - If `v == p`: Ignore (it's the direct bidirectional tree edge).
 *     - If `visited[v] == true`: It's a back-edge! `low[u] = min(low[u], disc[v])`.
 *     - If `visited[v] == false`: Recurse on `v`.
 *       - Upon return: `low[u] = min(low[u], low[v])`.
 *       - Bridge condition: If `low[v] > disc[u]`, then subtree at `v` has NO back-edges to `u` or any ancestor of `u`.
 *         Therefore, removing edge `(u, v)` completely isolates `v`'s component!
 * 
 * TIME COMPLEXITY:
 * - O(V + E): Single DFS traversal visiting each vertex and edge once.
 * 
 * SPACE COMPLEXITY:
 * - O(V + E) for the adjacency list and DFS recursion stack / tracking arrays.
 */

#include <iostream>
#include <vector>
#include <algorithm>

class BridgeFinder {
    int timer;
    std::vector<int> disc, low;
    std::vector<bool> visited;
    std::vector<std::pair<int, int>> bridges;

    void dfs(int u, int parent, const std::vector<std::vector<int>>& adj) {
        visited[u] = true;
        disc[u] = low[u] = ++timer;

        for (int v : adj[u]) {
            if (v == parent) continue; // Skip edge leading back to immediate parent

            if (visited[v]) {
                // Back-edge found: update low-link with discovery time of ancestor
                low[u] = std::min(low[u], disc[v]);
            } else {
                // Forward tree-edge
                dfs(v, u, adj);
                low[u] = std::min(low[u], low[v]);

                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // If the lowest vertex reachable from v was discovered strictly after u, edge (u, v) is a bridge.
                if (low[v] > disc[u]) {
                    bridges.push_back({u, v});
                }
            }
        }
    }

public:
    std::vector<std::pair<int, int>> getBridges(int V, const std::vector<std::vector<int>>& adj) {
        timer = 0;
        disc.assign(V, 0);
        low.assign(V, 0);
        visited.assign(V, false);
        bridges.clear();

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                dfs(i, -1, adj);
            }
        }
        return bridges;
    }
};

int main() {
    int V = 5;
    std::vector<std::vector<int>> adj(V);

    auto addEdge = [&](int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    };

    addEdge(1, 0);
    addEdge(0, 2);
    addEdge(2, 1);
    addEdge(0, 3);
    addEdge(3, 4);

    BridgeFinder bf;
    auto bridges = bf.getBridges(V, adj);

    std::cout << "Bridges (Critical Connections) in Graph:\n";
    for (const auto& [u, v] : bridges) {
        std::cout << u << " -- " << v << "\n";
    }

    return 0;
}
