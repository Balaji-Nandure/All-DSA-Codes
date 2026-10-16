/**
 * Problem: Cheapest Flights Within K Stops
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Dijkstra's algorithm finds the shortest path without edge count constraints.
 * - Here, a path is strictly constrained to at most `K` intermediate stops (i.e., at most `K + 1` flights/edges).
 * - A path with fewer stops but higher immediate cost might enable reaching the destination within K stops, whereas the globally cheapest path might exceed K stops.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Bellman-Ford Variant (Level-Synchronized K + 1 Relaxations):
 *   - Exactly like Bellman-Ford, but we run precisely `K + 1` iterations.
 *   - Crucial detail: In each iteration, relax using a SNAPSHOT of distances from the previous iteration (`prevDist`).
 *   - This strictly guarantees that iteration `step` only uses paths consisting of at most `step` edges, avoiding cascading multiple edges within a single step.
 * 
 * TIME COMPLEXITY:
 * - O((K + 1) * E): Exactly K + 1 passes over all flight edges.
 * 
 * SPACE COMPLEXITY:
 * - O(N) for distance snapshot arrays.
 */

#include <iostream>
#include <vector>
#include <algorithm>

int findCheapestPrice(int n, std::vector<std::vector<int>>& flights, int src, int dst, int k) {
    const int INF = 1e9;
    std::vector<int> dist(n, INF);
    dist[src] = 0;

    // We can use at most k + 1 flights (edges)
    for (int step = 0; step <= k; step++) {
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Copy dist to tempDist so that relaxations in the current iteration strictly extend paths by at most ONE edge.
        std::vector<int> tempDist = dist;

        for (const auto& flight : flights) {
            int u = flight[0];
            int v = flight[1];
            int price = flight[2];

            if (dist[u] != INF && dist[u] + price < tempDist[v]) {
                tempDist[v] = dist[u] + price;
            }
        }

        dist = tempDist;
    }

    return (dist[dst] >= INF) ? -1 : dist[dst];
}

int main() {
    int n = 4;
    std::vector<std::vector<int>> flights = {
        {0, 1, 100},
        {1, 2, 100},
        {2, 0, 100},
        {1, 3, 600},
        {2, 3, 200}
    };
    int src = 0, dst = 3, k = 1;

    int price = findCheapestPrice(n, flights, src, dst, k);
    std::cout << "Cheapest price within " << k << " stops: " << price << "\n"; // Expected: 700 (0 -> 1 -> 3)

    return 0;
}
