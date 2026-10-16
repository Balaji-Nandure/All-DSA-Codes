/**
 * Problem: Two Clique Problem (Check if Graph can be Divided into Two Cliques)
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - A clique is a subset of vertices such that every pair of distinct vertices is adjacent.
 * - Checking if a graph can be partitioned into two cliques is NP-complete in general without insight.
 * - However, there is a fundamental duality: In the COMPLEMENT graph G', any clique in G becomes an INDEPENDENT SET!
 * - Therefore, partitioning G into two cliques is IDENTICAL to partitioning G' into two independent sets — which means testing whether G' is BIPARTITE!
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Complement Graph Construction + Bipartite 2-Coloring:
 *   1. Construct complement graph `G'`:
 *      For all `u != v`, `G'[u][v] = 1 - G[u][v]`.
 *   2. Test if `G'` is bipartite using BFS 2-coloring:
 *      - If `G'` contains an odd-length cycle, it is not 2-colorable -> not bipartite -> graph G cannot be partitioned into two cliques.
 *      - If `G'` is bipartite, the two color partitions `C0` and `C1` in `G'` form two independent sets in `G'`.
 *      - By duality, `C0` and `C1` form two complete subgraphs (cliques) in the original graph `G`.
 * 
 * TIME COMPLEXITY:
 * - O(V^2): Constructing complement graph and BFS traversal.
 * 
 * SPACE COMPLEXITY:
 * - O(V^2) for the complement adjacency matrix/list and color array.
 */

#include <iostream>
#include <vector>
#include <queue>

bool isBipartite(int V, const std::vector<std::vector<int>>& adj) {
    std::vector<int> color(V, -1);

    for (int start = 0; start < V; start++) {
        if (color[start] != -1) continue;

        std::queue<int> q;
        q.push(start);
        color[start] = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (color[v] == -1) {
                    color[v] = 1 - color[u];
                    q.push(v);
                } else if (color[v] == color[u]) {
                    return false; // Odd cycle found
                }
            }
        }
    }

    return true;
}

bool canBeDividedIntoTwoCliques(int V, const std::vector<std::vector<int>>& graph) {
    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Build complement graph: A graph partitions into 2 cliques iff its complement graph is bipartite (2-colorable).
    std::vector<std::vector<int>> complementAdj(V);

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i != j && graph[i][j] == 0) {
                complementAdj[i].push_back(j);
            }
        }
    }

    return isBipartite(V, complementAdj);
}

int main() {
    int V = 5;
    // Graph with 2 cliques: {0, 1, 2} and {3, 4}
    std::vector<std::vector<int>> graph(V, std::vector<int>(V, 0));

    auto addEdge = [&](int u, int v) {
        graph[u][v] = 1;
        graph[v][u] = 1;
    };

    // Clique 1: 0 - 1 - 2
    addEdge(0, 1);
    addEdge(1, 2);
    addEdge(0, 2);

    // Clique 2: 3 - 4
    addEdge(3, 4);

    // Cross edges between cliques
    addEdge(1, 3);

    bool possible = canBeDividedIntoTwoCliques(V, graph);
    std::cout << "Can the graph be divided into two cliques? " << (possible ? "YES" : "NO") << "\n"; // Expected: YES

    return 0;
}
