/**
 * Problem: Chinese Postman Problem (Route Inspection Problem)
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Eulerian circuits visit every edge once if and only if all degrees are even.
 * - In real graphs, some vertices have odd degrees, which prevents a simple Eulerian circuit.
 * - The Chinese Postman Problem finds the shortest closed walk visiting every edge AT LEAST once, which requires finding the minimum total weight of duplicated edges between odd-degree vertices.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - All-Pairs Shortest Path + Bitmask DP for Minimum Weight Perfect Matching:
 *   1. Calculate total weight of all edges in the original graph: `totalWeight`.
 *   2. Find all vertices with ODD degrees. By the Handshaking Lemma, there is always an even number of such vertices: `2k`.
 *   3. If count of odd-degree vertices is 0, the graph is already Eulerian; return `totalWeight`.
 *   4. Compute all-pairs shortest paths using Floyd-Warshall.
 *   5. Pair up the odd-degree vertices such that the sum of shortest distances between paired vertices is minimized (Minimum Weight Perfect Matching).
 *      - We solve this using Bitmask DP: `minMatching(mask)` represents the minimum distance to match remaining odd vertices in `mask`.
 *   6. The final answer is `totalWeight + minMatchingCost`.
 * 
 * TIME COMPLEXITY:
 * - O(V^3 + 2^(2k) * (2k)^2) where 2k is the number of odd-degree vertices.
 * 
 * SPACE COMPLEXITY:
 * - O(V^2 + 2^(2k)) for shortest distance matrix and bitmask memo table.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

const int INF = 1e8;

class ChinesePostman {
    int oddCount;
    std::vector<int> oddVertices;
    std::vector<std::vector<int>> dist;
    std::vector<int> memo;

    int minMatching(int mask) {
        if (mask == 0) return 0; // All odd vertices paired
        if (memo[mask] != -1) return memo[mask];

        int minCost = INF;

        // Pick first unmatched vertex in mask
        int first = -1;
        for (int i = 0; i < oddCount; i++) {
            if (mask & (1 << i)) {
                first = i;
                break;
            }
        }

        // Pair 'first' with every other available unmatched vertex 'second'
        for (int second = first + 1; second < oddCount; second++) {
            if (mask & (1 << second)) {
                int pairDistance = dist[oddVertices[first]][oddVertices[second]];
                int newMask = mask ^ (1 << first) ^ (1 << second);
                minCost = std::min(minCost, pairDistance + minMatching(newMask));
            }
        }

        return memo[mask] = minCost;
    }

public:
    int solve(int V, const std::vector<std::vector<std::pair<int, int>>>& adj) {
        dist.assign(V, std::vector<int>(V, INF));
        for (int i = 0; i < V; i++) dist[i][i] = 0;

        int totalWeight = 0;
        std::vector<int> degree(V, 0);

        for (int u = 0; u < V; u++) {
            for (const auto& [v, w] : adj[u]) {
                if (u < v) { // Count undirected edge once
                    totalWeight += w;
                    degree[u]++;
                    degree[v]++;
                }
                dist[u][v] = std::min(dist[u][v], w);
            }
        }

        // Floyd-Warshall for all-pairs shortest paths
        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }

        // Find vertices with odd degrees
        oddVertices.clear();
        for (int i = 0; i < V; i++) {
            if (degree[i] % 2 != 0) {
                oddVertices.push_back(i);
            }
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // If all degrees are even, graph is Eulerian; otherwise, add minimum weight matching among odd-degree nodes.
        if (oddVertices.empty()) {
            return totalWeight;
        }

        oddCount = oddVertices.size();
        memo.assign(1 << oddCount, -1);
        int addedDistance = minMatching((1 << oddCount) - 1);

        return totalWeight + addedDistance;
    }
};

int main() {
    int V = 4;
    std::vector<std::vector<std::pair<int, int>>> adj(V);

    auto addEdge = [&](int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    };

    addEdge(0, 1, 3);
    addEdge(1, 2, 4);
    addEdge(2, 3, 5);
    addEdge(3, 0, 2);
    addEdge(0, 2, 6);

    ChinesePostman cp;
    int minRoute = cp.solve(V, adj);
    std::cout << "Minimum Route Inspection Distance: " << minRoute << "\n";

    return 0;
}
