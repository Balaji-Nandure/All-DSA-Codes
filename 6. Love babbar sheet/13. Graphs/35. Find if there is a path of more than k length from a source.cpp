/**
 * Problem: Find if There is a Path of More Than K Length from a Source
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Shortest path problems (Dijkstra, BFS) have optimal substructure and polynomial solutions.
 * - Finding a SIMPLE path (no repeated vertices) of weight >= K is NP-complete (Hamiltonian Path is a special case).
 * - Hence, greedy or dynamic programming algorithms fail; exhaustive Backtracking DFS is required.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Backtracking Depth-First Search:
 *   - Start DFS from `src` with remaining distance `k`.
 *   - Base condition: If `k <= 0`, a valid simple path of length >= K has already been accumulated; return `true` immediately.
 *   - Mark `visited[src] = true`.
 *   - Iterate through all neighbors `(v, weight)` of `src`:
 *     - If `!visited[v]`:
 *       - Recurse: `hasPath(v, k - weight)`.
 *       - If child call returns `true`, propagate `true` up the call stack immediately (early pruning).
 *   - Backtrack: Unmark `visited[src] = false` to allow `src` to be part of alternative path branches.
 * 
 * TIME COMPLEXITY:
 * - O(V!): In the worst case (complete graph), checks all simple permutations of vertices.
 * 
 * SPACE COMPLEXITY:
 * - O(V) for the visited boolean array and DFS recursion stack.
 */

#include <iostream>
#include <vector>

struct Edge {
    int to;
    int weight;
};

class Solution {
    bool dfs(int u, int k, const std::vector<std::vector<Edge>>& adj, std::vector<bool>& visited) {
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Path weight has exceeded or met requirement k; return true immediately to prune all further recursion.
        if (k <= 0) return true;

        visited[u] = true;

        for (const auto& edge : adj[u]) {
            int v = edge.to;
            int w = edge.weight;

            if (!visited[v]) {
                if (dfs(v, k - w, adj, visited)) {
                    return true;
                }
            }
        }

        // Backtrack: unmark vertex to allow exploration in other candidate paths
        visited[u] = false;
        return false;
    }

public:
    bool pathMoreThanK(int V, const std::vector<std::vector<Edge>>& adj, int src, int k) {
        std::vector<bool> visited(V, false);
        return dfs(src, k, adj, visited);
    }
};

int main() {
    int V = 9;
    std::vector<std::vector<Edge>> adj(V);

    auto addEdge = [&](int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    };

    addEdge(0, 1, 4);
    addEdge(0, 7, 8);
    addEdge(1, 2, 8);
    addEdge(1, 7, 11);
    addEdge(2, 3, 7);
    addEdge(2, 8, 2);
    addEdge(2, 5, 4);
    addEdge(3, 4, 9);
    addEdge(3, 5, 14);
    addEdge(4, 5, 10);
    addEdge(5, 6, 2);
    addEdge(6, 7, 1);
    addEdge(6, 8, 6);
    addEdge(7, 8, 7);

    Solution sol;
    int src = 0, k = 60;
    std::cout << "Is there a simple path from 0 of length >= 60? " 
              << (sol.pathMoreThanK(V, adj, src, k) ? "YES" : "NO") << "\n"; // Expected: YES (sum >= 60 exists)

    int k2 = 100;
    std::cout << "Is there a simple path from 0 of length >= 100? " 
              << (sol.pathMoreThanK(V, adj, src, k2) ? "YES" : "NO") << "\n"; // Expected: NO

    return 0;
}
