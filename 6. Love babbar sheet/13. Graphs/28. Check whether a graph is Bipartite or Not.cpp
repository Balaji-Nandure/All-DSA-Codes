/**
 * Problem: Check Whether a Graph is Bipartite or Not
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - A bipartite graph is one whose vertices can be divided into two disjoint sets U and V such that every edge connects a vertex in U to one in V.
 * - Crucial graph theory property: A graph is bipartite IF AND ONLY IF it contains NO cycle of odd length.
 * - Checking bipartiteness is equivalent to testing whether the graph is 2-colorable.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Breadth-First Search (BFS) 2-Coloring:
 *   - Maintain `color[V]` array initialized to `-1` (unvisited).
 *   - For every disconnected component, if `color[i] == -1`:
 *     - Color `color[i] = 0` and enqueue `i`.
 *     - While queue is not empty:
 *       - Pop `u`.
 *       - For each neighbor `v` of `u`:
 *         - If `color[v] == -1`, assign opposite color: `color[v] = 1 - color[u]`, and enqueue `v`.
 *         - If `color[v] == color[u]`, two adjacent vertices have the same color -> odd cycle detected -> NOT bipartite!
 * 
 * TIME COMPLEXITY:
 * - O(V + E): Standard BFS checking each vertex and edge once.
 * 
 * SPACE COMPLEXITY:
 * - O(V) for the color array and BFS queue.
 */

#include <iostream>
#include <vector>
#include <queue>

bool isBipartite(int V, const std::vector<std::vector<int>>& adj) {
    std::vector<int> color(V, -1); // -1: uncolored, 0: color A, 1: color B

    for (int start = 0; start < V; start++) {
        if (color[start] != -1) continue;

        std::queue<int> q;
        q.push(start);
        color[start] = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                // If neighbor is not yet colored, assign complementary color
                if (color[v] == -1) {
                    color[v] = 1 - color[u];
                    q.push(v);
                } 
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // If an adjacent vertex already possesses the identical color, an odd-length cycle exists; graph cannot be bipartite.
                else if (color[v] == color[u]) {
                    return false;
                }
            }
        }
    }

    return true;
}

int main() {
    int V = 4;
    std::vector<std::vector<int>> adj(V);

    auto addEdge = [&](int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    };

    // Even cycle: 0 - 1 - 2 - 3 - 0 (Bipartite)
    addEdge(0, 1);
    addEdge(1, 2);
    addEdge(2, 3);
    addEdge(3, 0);

    std::cout << "Is 4-cycle graph bipartite? " << (isBipartite(V, adj) ? "YES" : "NO") << "\n"; // Expected: YES

    // Add odd cycle chord: 0 - 2 (forms triangle 0-1-2)
    addEdge(0, 2);
    std::cout << "Is graph with odd cycle bipartite? " << (isBipartite(V, adj) ? "YES" : "NO") << "\n"; // Expected: NO

    return 0;
}
