/**
 * Problem: Implement Bellman-Ford Algorithm
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Dijkstra's algorithm fails when edges have negative weights because greedy finalized nodes may later be updated via negative paths.
 * - Bellman-Ford works with arbitrary edge weights (positive or negative).
 * - It can definitively detect the presence of negative weight cycles reachable from the source.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Dynamic Programming over Path Lengths (V - 1 Relaxations):
 *   - A simple path in a graph with `V` vertices can contain at most `V - 1` edges.
 *   - Initialize `dist[src] = 0` and all other `dist[v] = INF`.
 *   - Relax ALL `E` edges repeatedly for `V - 1` rounds:
 *     - If `dist[u] != INF` and `dist[u] + weight < dist[v]`, update `dist[v] = dist[u] + weight`.
 *   - Perform an additional `V`-th round of relaxation:
 *     - If any edge can STILL be relaxed, a negative weight cycle exists reachable from `src`.
 * 
 * TIME COMPLEXITY:
 * - O(V * E): We iterate over all E edges V - 1 times.
 * 
 * SPACE COMPLEXITY:
 * - O(V) for the distance array.
 */

#include <iostream>
#include <vector>
#include <climits>

struct Edge {
    int u, v, weight;
};

// Returns distances from src; if negative cycle reachable, returns empty vector
std::vector<int> bellmanFord(int V, const std::vector<Edge>& edges, int src, bool& hasNegativeCycle) {
    const int INF = 1e8; // Use large sentinel to avoid overflow on negative weights
    std::vector<int> dist(V, INF);
    dist[src] = 0;

    // Relax all edges V - 1 times
    for (int i = 1; i <= V - 1; i++) {
        for (const auto& edge : edges) {
            if (dist[edge.u] != INF && dist[edge.u] + edge.weight < dist[edge.v]) {
                dist[edge.v] = dist[edge.u] + edge.weight;
            }
        }
    }

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // On the V-th relaxation, any further reduction proves a negative weight cycle exists.
    hasNegativeCycle = false;
    for (const auto& edge : edges) {
        if (dist[edge.u] != INF && dist[edge.u] + edge.weight < dist[edge.v]) {
            hasNegativeCycle = true;
            return {};
        }
    }

    return dist;
}

int main() {
    int V = 5;
    std::vector<Edge> edges = {
        {0, 1, -1},
        {0, 2, 4},
        {1, 2, 3},
        {1, 3, 2},
        {1, 4, 2},
        {3, 2, 5},
        {3, 1, 1},
        {4, 3, -3}
    };

    bool hasCycle = false;
    std::vector<int> distances = bellmanFord(V, edges, 0, hasCycle);

    if (hasCycle) {
        std::cout << "Negative weight cycle detected!\n";
    } else {
        std::cout << "Shortest distances from source 0:\n";
        for (int i = 0; i < V; i++) {
            std::cout << "Node " << i << " -> " << distances[i] << "\n";
        }
    }

    return 0;
}
