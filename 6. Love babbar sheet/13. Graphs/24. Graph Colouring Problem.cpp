/**
 * Problem: Graph Coloring Problem (Greedy Algorithm for Vertex Coloring)
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In standard traversals, vertices are processed sequentially.
 * - Vertex coloring requires assigning colors (labels) to every vertex such that no two adjacent vertices share the same color.
 * - Finding the absolute chromatic number is NP-complete; the greedy coloring algorithm provides an efficient upper-bounded coloring (at most d + 1 colors, where d is the max degree).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Greedy Smallest Available Color Assignment:
 *   1. Initialize `color[V]` array with `-1` (unassigned).
 *   2. Assign `color[0] = 0`.
 *   3. Maintain a boolean array `available[V]` to track colors forbidden by neighbors.
 *   4. For each vertex `u` from 1 to `V - 1`:
 *      - Inspect all adjacent neighbors `v`: if `color[v] != -1`, mark `available[color[v]] = false`.
 *      - Find the first color `c` where `available[c] == true`.
 *      - Assign `color[u] = c`.
 *      - Reset `available` array flags for subsequent vertices.
 * 
 * TIME COMPLEXITY:
 * - O(V^2 + E): Each vertex checks its neighbors and finds the lowest unused color.
 * 
 * SPACE COMPLEXITY:
 * - O(V) for the color array and availability lookup table.
 */

#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> greedyColoring(int V, std::vector<std::vector<int>>& adj) {
    std::vector<int> result(V, -1);
    result[0] = 0; // First vertex gets color 0

    // available[cr] == false means color cr is already used by an adjacent neighbor
    std::vector<bool> available(V, true);

    for (int u = 1; u < V; u++) {
        // Mark colors of all adjacent colored neighbors as unavailable
        for (int v : adj[u]) {
            if (result[v] != -1) {
                available[result[v]] = false;
            }
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Select the smallest non-negative integer color not assigned to any adjacent neighbor.
        int cr;
        for (cr = 0; cr < V; cr++) {
            if (available[cr]) {
                break;
            }
        }

        result[u] = cr; // Assign lowest available color

        // Reset available flags for next iteration
        for (int v : adj[u]) {
            if (result[v] != -1) {
                available[result[v]] = true;
            }
        }
    }

    return result;
}

int main() {
    int V = 5;
    std::vector<std::vector<int>> adj(V);

    auto addEdge = [&](int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    };

    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 2);
    addEdge(1, 3);
    addEdge(2, 3);
    addEdge(3, 4);

    std::vector<int> colors = greedyColoring(V, adj);

    std::cout << "Greedy Vertex Colors:\n";
    for (int i = 0; i < V; i++) {
        std::cout << "Vertex " << i << " ---> Color " << colors[i] << "\n";
    }

    return 0;
}
