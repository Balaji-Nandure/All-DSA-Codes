/**
 * Problem: Minimum Edges to Reverse to Make Path from Source to Destination
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - A directed path might not exist from `src` to `dst`.
 * - We are permitted to reverse directed edges, and seek to minimize the total count of reversals needed.
 * - This transformation can be cast as an unweighted / 0-1 weighted shortest path problem.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - 0-1 Breadth-First Search (0-1 BFS with Deque):
 *   - For every original directed edge `u -> v`:
 *     - Add edge `u -> v` with weight `0` (traversing along existing direction costs 0 reversals).
 *     - Add reverse edge `v -> u` with weight `1` (traversing opposite to existing direction costs 1 reversal).
 *   - Now, find the shortest path from `src` to `dst` in this graph where all edge weights are strictly {0, 1}.
 *   - 0-1 BFS using `std::deque`:
 *     - If relaxed edge has weight 0, push to the FRONT of the deque (maintains monotonic non-decreasing distance order).
 *     - If relaxed edge has weight 1, push to the BACK of the deque.
 *   - This achieves optimal O(V + E) shortest path without the O(log V) priority queue overhead of Dijkstra!
 * 
 * TIME COMPLEXITY:
 * - O(V + E): Each vertex is popped at most once in 0-1 BFS.
 * 
 * SPACE COMPLEXITY:
 * - O(V + E) for adjacency list, distance array, and deque.
 */

#include <iostream>
#include <vector>
#include <deque>
#include <climits>

struct Edge {
    int to;
    int weight; // 0: original direction, 1: reversed direction
};

int minReversals(int V, const std::vector<std::pair<int, int>>& originalEdges, int src, int dst) {
    std::vector<std::vector<Edge>> adj(V);

    for (const auto& [u, v] : originalEdges) {
        adj[u].push_back({v, 0}); // Cost 0 to use edge as-is
        adj[v].push_back({u, 1}); // Cost 1 to flip and use reversed edge
    }

    std::vector<int> dist(V, INT_MAX);
    std::deque<int> dq;

    dist[src] = 0;
    dq.push_back(src);

    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();

        if (u == dst) {
            return dist[dst];
        }

        for (const auto& edge : adj[u]) {
            int v = edge.to;
            int weight = edge.weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;

                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // 0-1 BFS: Push 0-weight extensions to front, 1-weight extensions to back to preserve priority ordering.
                if (weight == 0) {
                    dq.push_front(v);
                } else {
                    dq.push_back(v);
                }
            }
        }
    }

    return (dist[dst] == INT_MAX) ? -1 : dist[dst];
}

int main() {
    int V = 7;
    std::vector<std::pair<int, int>> edges = {
        {0, 1}, {2, 1}, {2, 3}, {5, 1}, {4, 5}, {6, 4}, {6, 3}
    };
    int src = 0, dst = 6;

    int reversals = minReversals(V, edges, src, dst);
    std::cout << "Minimum edge reversals from " << src << " to " << dst << ": " << reversals << "\n"; // Expected: 2

    return 0;
}
