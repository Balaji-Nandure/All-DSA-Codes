/**
 * Problem: M-Coloring Problem
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - The greedy coloring problem assigns colors to minimize the total count used.
 * - M-Coloring is a hard DECISION problem: Given a fixed limit `M`, does there exist ANY assignment of colors {1, 2, ..., M}
 *   such that no two adjacent vertices share the same color?
 * - This is an NP-complete problem requiring systematic backtracking.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Backtracking Vertex Color Assignment:
 *   - Function `solve(node, V, m, color, graph)`:
 *     1. Base Case: If `node == V`, all vertices have been successfully assigned compatible colors; return `true`.
 *     2. For each color `c` from 1 to `m`:
 *        - Safety check: Verify if ANY adjacent neighbor `v` already has `color[v] == c`.
 *        - If safe:
 *          - Assign `color[node] = c`.
 *          - Recurse: `solve(node + 1, ...)`.
 *          - If recursion returns `true`, propagate `true` immediately.
 *          - Backtrack: Reset `color[node] = 0`.
 *     3. If no color from 1 to `m` is valid, return `false`.
 * 
 * TIME COMPLEXITY:
 * - O(M^V): In the worst case, each vertex tries M colors.
 * 
 * SPACE COMPLEXITY:
 * - O(V) for the recursion stack and color array.
 */

#include <iostream>
#include <vector>

bool isSafe(int node, int col, int V, const std::vector<std::vector<int>>& graph, const std::vector<int>& color) {
    for (int k = 0; k < V; k++) {
        if (graph[node][k] && color[k] == col) {
            return false;
        }
    }
    return true;
}

bool solve(int node, int V, int m, std::vector<int>& color, const std::vector<std::vector<int>>& graph) {
    if (node == V) return true;

    for (int col = 1; col <= m; col++) {
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Only attempt assigning color col to current node if none of its adjacent neighbors have already chosen col.
        if (isSafe(node, col, V, graph, color)) {
            color[node] = col;

            if (solve(node + 1, V, m, color, graph)) {
                return true;
            }

            color[node] = 0; // Backtrack
        }
    }

    return false;
}

bool graphColoring(int V, const std::vector<std::vector<int>>& graph, int m) {
    std::vector<int> color(V, 0);
    return solve(0, V, m, color, graph);
}

int main() {
    int V = 4;
    // Graph K4 (Complete graph on 4 vertices)
    std::vector<std::vector<int>> graph = {
        {0, 1, 1, 1},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {1, 1, 1, 0}
    };

    int m = 3;
    std::cout << "Can K4 be colored with 3 colors? " << (graphColoring(V, graph, m) ? "YES" : "NO") << "\n"; // Expected: NO (chromatic number of K4 is 4)

    int m2 = 4;
    std::cout << "Can K4 be colored with 4 colors? " << (graphColoring(V, graph, m2) ? "YES" : "NO") << "\n"; // Expected: YES

    return 0;
}
