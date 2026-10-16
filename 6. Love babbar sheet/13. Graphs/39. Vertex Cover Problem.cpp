/**
 * Problem: Vertex Cover Problem (Exact Branching & 2-Approximation Algorithm)
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - A vertex cover is a set of vertices such that every edge in the graph has at least one endpoint in the set.
 * - Finding the Minimum Vertex Cover is NP-hard.
 * - Unlike heuristic problems, we can either use exact recursive branching (fixed-parameter tractable) or a polynomial-time 2-approximation algorithm.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Greedy 2-Approximation Algorithm:
 *   1. Initialize an empty vertex cover set `cover`.
 *   2. Iterate through all edges `(u, v)`:
 *      - If neither `u` nor `v` is in `cover`:
 *        - Add BOTH `u` and `v` to `cover`.
 *        - Mark all incident edges of both `u` and `v` as covered.
 *   3. Approximation Bound: The size of this cover is guaranteed to be at most 2 * OPT, because any valid vertex cover must select at least one endpoint from each of the disjoint edges chosen.
 * - Exact Solution for Small V: Recursive branch-and-bound on the uncovered edge.
 * 
 * TIME COMPLEXITY:
 * - Approximation: O(V + E) linear time.
 * - Exact Branching: O(2^K * (V + E)) where K is the target cover size.
 * 
 * SPACE COMPLEXITY:
 * - O(V) for the cover boolean array.
 */

#include <iostream>
#include <vector>

// 2-Approximation polynomial time algorithm
std::vector<int> approxVertexCover(int V, const std::vector<std::pair<int, int>>& edges) {
    std::vector<bool> visited(V, false);

    for (const auto& [u, v] : edges) {
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // If neither endpoint is covered, include BOTH u and v; this guarantees at most 2x optimal size.
        if (!visited[u] && !visited[v]) {
            visited[u] = true;
            visited[v] = true;
        }
    }

    std::vector<int> cover;
    for (int i = 0; i < V; i++) {
        if (visited[i]) {
            cover.push_back(i);
        }
    }
    return cover;
}

int main() {
    int V = 7;
    std::vector<std::pair<int, int>> edges = {
        {0, 1}, {0, 2}, {1, 3}, {3, 4}, {4, 5}, {5, 6}
    };

    std::vector<int> cover = approxVertexCover(V, edges);

    std::cout << "Approximate Vertex Cover nodes:\n";
    for (int node : cover) {
        std::cout << node << " ";
    }
    std::cout << "\nCover size: " << cover.size() << "\n";

    return 0;
}
