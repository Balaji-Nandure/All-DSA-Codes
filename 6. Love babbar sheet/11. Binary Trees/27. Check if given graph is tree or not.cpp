/**
 * Problem: Check if Given Graph is a Tree or Not
 * Category: Binary Trees / Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In all tree problems so far, the hierarchical parent-child pointers were already established.
 * - Here, we receive an arbitrary undirected GRAPH: `G = (V, E)` and must prove mathematically
 *   whether it satisfies the axiomatic definition of a Tree.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Axiomatic Graph Theory:
 *   - A connected undirected graph with V vertices is a Tree IF AND ONLY IF:
 *     1. Number of edges is strictly `E == V - 1`.
 *     2. The graph contains NO CYCLES.
 *     3. The graph is fully CONNECTED (all V vertices belong to a single connected component).
 *   - Algorithm:
 *     - If `E != V - 1`: Immediately return false!
 *     - Run DFS/BFS starting from vertex 0, passing the parent of each node.
 *     - If an adjacent node is already visited and is NOT the parent of the current node -> CYCLE detected!
 *     - After traversal, verify that all V vertices were reached (Connectedness).
 * 
 * TIME COMPLEXITY:
 * - O(V + E): Single DFS traversal.
 * 
 * SPACE COMPLEXITY:
 * - O(V + E) for adjacency list and visited array.
 */

#include <iostream>
#include <vector>

bool isCyclicDFS(int u, int parent, const std::vector<std::vector<int>>& adj, std::vector<bool>& visited) {
    visited[u] = true;

    for (int v : adj[u]) {
        if (!visited[v]) {
            if (isCyclicDFS(v, u, adj, visited)) return true;
        } else if (v != parent) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // An already visited neighbor that is NOT our direct parent proves the existence of a cycle!
            return true;
        }
    }

    return false;
}

bool isTree(int V, int E, const std::vector<std::pair<int, int>>& edges) {
    // Property 1: A tree with V vertices must have exactly V - 1 edges
    if (E != V - 1) return false;

    // Build adjacency list
    std::vector<std::vector<int>> adj(V);
    for (const auto& [u, v] : edges) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    std::vector<bool> visited(V, false);

    // Property 2: Must be acyclic
    if (isCyclicDFS(0, -1, adj, visited)) {
        return false;
    }

    // Property 3: Must be fully connected
    for (int i = 0; i < V; i++) {
        if (!visited[i]) return false;
    }

    return true;
}

int main() {
    int V = 5, E = 4;
    std::vector<std::pair<int, int>> edges1 = {
        {1, 0}, {0, 2}, {0, 3}, {3, 4}
    };
    std::cout << "Graph 1 is a tree: " << (isTree(V, E, edges1) ? "Yes" : "No") << "\n"; // Yes

    std::vector<std::pair<int, int>> edges2 = {
        {1, 0}, {0, 2}, {2, 1}, {0, 3}
    };
    std::cout << "Graph 2 is a tree: " << (isTree(V, E, edges2) ? "Yes" : "No") << "\n"; // No (contains cycle 0-1-2)

    return 0;
}
