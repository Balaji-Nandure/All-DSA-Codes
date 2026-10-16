/**
 * Problem: Detect Negative Cycle in a Graph
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Standard Bellman-Ford runs from a single specified source vertex; it will MISS negative cycles that are disconnected from that source.
 * - To detect ANY negative cycle anywhere in the entire graph, we must ensure all components are simultaneously reachable.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Bellman-Ford with Zero-Initialization:
 *   - Instead of setting `dist[src] = 0` and all others to `INF`, initialize `dist[i] = 0` for ALL vertices `0 <= i < V`.
 *   - (This is equivalent to creating a virtual super-source connected to all vertices with weight-0 directed edges).
 *   - Relax all `E` edges for `V - 1` iterations.
 *   - On the `V`-th iteration:
 *     - If `dist[u] + weight < dist[v]`, then a negative weight cycle exists in the graph!
 * 
 * TIME COMPLEXITY:
 * - O(V * E): V passes over all E edges.
 * 
 * SPACE COMPLEXITY:
 * - O(V) for the distance array.
 */

#include <iostream>
#include <vector>

struct Edge {
    int u, v, weight;
};

bool isNegativeWeightCyclePresent(int V, const std::vector<Edge>& edges) {
    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Initialize dist array to 0 across ALL vertices to act as a virtual super-source covering disconnected components.
    std::vector<int> dist(V, 0);

    // Relax all edges V - 1 times
    for (int i = 1; i <= V - 1; i++) {
        for (const auto& edge : edges) {
            if (dist[edge.u] + edge.weight < dist[edge.v]) {
                dist[edge.v] = dist[edge.u] + edge.weight;
            }
        }
    }

    // Check for negative-weight cycle on V-th pass
    for (const auto& edge : edges) {
        if (dist[edge.u] + edge.weight < dist[edge.v]) {
            return true; // Negative weight cycle exists
        }
    }

    return false;
}

int main() {
    int V = 4;
    // Graph containing negative cycle: 1 -> 2 (weight -1), 2 -> 3 (weight -2), 3 -> 1 (weight 1) => sum = -2
    std::vector<Edge> edges = {
        {0, 1, 1},
        {1, 2, -1},
        {2, 3, -2},
        {3, 1, 1}
    };

    bool hasCycle = isNegativeWeightCyclePresent(V, edges);
    std::cout << "Contains negative weight cycle? " << (hasCycle ? "YES" : "NO") << "\n"; // Expected: YES

    return 0;
}
