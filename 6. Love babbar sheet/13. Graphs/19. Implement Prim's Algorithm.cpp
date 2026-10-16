/**
 * Problem: Implement Prim's Algorithm for Minimum Spanning Tree (MST)
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Kruskal's algorithm is global and edge-based, requiring sorting all edges.
 * - Prim's algorithm is vertex-based and grows a single contiguous tree outward from a seed vertex.
 * - Like Dijkstra, it uses a min-heap priority queue, but relaxes edges based purely on the connecting edge weight rather than cumulative path distance from source.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Min-Priority Queue Cut-Property Growth:
 *   1. Track `inMST[V]` array initialized to false.
 *   2. Min-heap stores tuples `{weight, node, parent}`.
 *   3. Seed the heap with `{0, 0, -1}`.
 *   4. While the heap is non-empty:
 *      - Pop the cheapest edge `{w, u, parent}`.
 *      - If `inMST[u] == true`, discard it (already bridged).
 *      - Mark `inMST[u] = true`, add `w` to `totalWeight`, record edge `(parent, u)`.
 *      - For each neighbor `(v, weight)` of `u`:
 *        - If `!inMST[v]`, push `{weight, v, u}` into the min-heap.
 *   5. Terminates when all reachable vertices are included.
 * 
 * TIME COMPLEXITY:
 * - O(E log V) using an adjacency list and binary min-heap.
 * 
 * SPACE COMPLEXITY:
 * - O(V + E) for the adjacency list and priority queue.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

struct Edge {
    int to;
    int weight;
};

int primsMST(int V, std::vector<std::vector<Edge>>& adj, std::vector<std::pair<int, int>>& mstEdges) {
    // Min-heap: {weight, node, parent}
    std::priority_queue<std::tuple<int, int, int>,
                        std::vector<std::tuple<int, int, int>>,
                        std::greater<std::tuple<int, int, int>>> pq;

    std::vector<bool> inMST(V, false);
    int totalCost = 0;

    pq.push({0, 0, -1}); // Start from vertex 0

    while (!pq.empty()) {
        auto [w, u, parent] = pq.top();
        pq.pop();

        if (inMST[u]) continue;

        inMST[u] = true;
        totalCost += w;
        if (parent != -1) {
            mstEdges.push_back({parent, u});
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Unlike Dijkstra which accumulates path sum dist[u] + w, Prim prioritizes the raw connecting edge weight to expand the cut.
        for (const auto& edge : adj[u]) {
            int v = edge.to;
            int weight = edge.weight;

            if (!inMST[v]) {
                pq.push({weight, v, u});
            }
        }
    }

    return totalCost;
}

int main() {
    int V = 5;
    std::vector<std::vector<Edge>> adj(V);

    auto addUndirectedEdge = [&](int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    };

    addUndirectedEdge(0, 1, 2);
    addUndirectedEdge(0, 3, 6);
    addUndirectedEdge(1, 2, 3);
    addUndirectedEdge(1, 3, 8);
    addUndirectedEdge(1, 4, 5);
    addUndirectedEdge(2, 4, 7);
    addUndirectedEdge(3, 4, 9);

    std::vector<std::pair<int, int>> mstEdges;
    int mstCost = primsMST(V, adj, mstEdges);

    std::cout << "Prim's MST Total Cost: " << mstCost << "\n"; // Expected: 16
    std::cout << "MST Edges:\n";
    for (const auto& [u, v] : mstEdges) {
        std::cout << u << " - " << v << "\n";
    }

    return 0;
}
