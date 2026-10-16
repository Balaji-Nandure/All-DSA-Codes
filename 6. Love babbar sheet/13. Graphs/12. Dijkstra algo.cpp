/**
 * Problem: Dijkstra's Shortest Path Algorithm
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - BFS only works for unweighted graphs (or uniform weight = 1).
 * - When edges have non-negative weights, the path with the fewest hops might have a much greater total sum than a path with more hops.
 * - Dijkstra uses a greedy min-heap priority queue to expand the currently closest frontier vertex.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Min-Priority Queue (Greedy Relaxation):
 *   - Maintain `dist[u]` initialized to infinity, with `dist[src] = 0`.
 *   - Min-heap stores pairs `(distance, vertex)`.
 *   - At each step, pop `(d, u)` with the smallest tentative distance.
 *   - If `d > dist[u]`, this is an outdated entry from an earlier relaxation; discard it.
 *   - For each neighbor `v` of `u` with edge weight `w`:
 *     - If `dist[u] + w < dist[v]`:
 *       - Update `dist[v] = dist[u] + w`.
 *       - Push `(dist[v], v)` into the priority queue.
 *   - Condition: All edge weights must be non-negative.
 * 
 * TIME COMPLEXITY:
 * - O((V + E) log V) using adjacency list and binary min-heap.
 * 
 * SPACE COMPLEXITY:
 * - O(V + E) for the adjacency list and priority queue.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

struct Edge {
    int to;
    int weight;
};

std::vector<int> dijkstra(int V, std::vector<std::vector<Edge>>& adj, int src) {
    std::vector<int> dist(V, INT_MAX);
    // Min-heap storing pair: {distance, node}
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        // If distance is already greater than best known, skip (lazy deletion)
        if (d > dist[u]) continue;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Relax edge (u -> v): If path through u provides a strictly shorter path to v, update and push to priority queue.
        for (const auto& edge : adj[u]) {
            int v = edge.to;
            int weight = edge.weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main() {
    int V = 5;
    std::vector<std::vector<Edge>> adj(V);

    // Build sample directed weighted graph
    adj[0].push_back({1, 4});
    adj[0].push_back({2, 1});
    adj[2].push_back({1, 2});
    adj[1].push_back({3, 1});
    adj[2].push_back({3, 5});
    adj[3].push_back({4, 3});

    int src = 0;
    std::vector<int> distances = dijkstra(V, adj, src);

    std::cout << "Shortest distances from source " << src << ":\n";
    for (int i = 0; i < V; i++) {
        std::cout << "Node " << i << " : " << (distances[i] == INT_MAX ? -1 : distances[i]) << "\n";
    }

    return 0;
}
