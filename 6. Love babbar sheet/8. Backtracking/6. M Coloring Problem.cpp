#include <iostream>
#include <vector>

using namespace std;

/**
 * Problem: M Coloring Problem
 * 
 * Given an undirected graph and an integer M. Determine if the graph can be 
 * colored with at most M colors such that no two adjacent vertices have the same color.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - This is graph vertex coloring (Chromatic Number decision problem, NP-Complete).
 * - Unlike Bipartite checking (2-coloring, which is solvable in O(V + E) via BFS/DFS),
 *   M-Coloring for M >= 3 requires exhaustive Backtracking with constraint validation.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Vertex-by-Vertex Backtracking:
 *   1. Represent assigned colors in an array `color[0 ... V-1]` initialized to 0 (uncolored).
 *   2. For vertex `u`:
 *      Try assigning each color `c` from 1 to M:
 *      - Safety Check: Iterate over all adjacent neighbors `v` of `u`.
 *        If any neighbor `v` already has color `c`, then color `c` is invalid for vertex `u`.
 *      - If valid:
 *        Assign `color[u] = c`.
 *        Recursively solve for vertex `u + 1`.
 *        If the recursive call returns true: propagate success upwards.
 *        Otherwise: backtrack by setting `color[u] = 0`.
 *   3. Base Case:
 *      If vertex index `u == V`, all vertices have been successfully and legally colored. Return true.
 */

class Solution {
    bool isSafe(int u, int c, int V, bool graph[101][101], vector<int>& color) {
        for (int v = 0; v < V; v++) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // If there is an edge between u and v, they cannot share color c
            if (graph[u][v] && color[v] == c) {
                return false;
            }
        }
        return true;
    }

    bool solve(int u, int M, int V, bool graph[101][101], vector<int>& color) {
        // Base case: All V vertices successfully colored
        if (u == V) {
            return true;
        }

        // Try all M available colors
        for (int c = 1; c <= M; c++) {
            if (isSafe(u, c, V, graph, color)) {
                color[u] = c; // Assign color c to vertex u

                if (solve(u + 1, M, V, graph, color)) {
                    return true;
                }

                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Backtrack: Remove color assignment to test next color candidate
                color[u] = 0;
            }
        }

        return false;
    }

public:
    bool graphColoring(bool graph[101][101], int M, int V) {
        vector<int> color(V, 0);
        return solve(0, M, V, graph, color);
    }
};

int main() {
    Solution sol;
    int V = 4;
    int M = 3;
    bool graph[101][101] = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0}
    };

    if (sol.graphColoring(graph, M, V)) {
        cout << "Graph can be colored with " << M << " colors.\n";
    } else {
        cout << "Graph CANNOT be colored with " << M << " colors.\n";
    }
    // Expected: Graph can be colored with 3 colors.

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(M^V) in the worst case where every vertex tests up to M colors.
 *   Pruning eliminates non-viable coloring prefixes early.
 * - Space Complexity: O(V) for the color array and recursion stack.
 */
