/**
 * Problem: Implement Kruskal's Algorithm for Minimum Spanning Tree (MST)
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Prim's algorithm grows an MST outward from an arbitrary start vertex one edge at a time.
 * - Kruskal's algorithm is edge-centric: it globally examines all edges in ascending order of weights.
 * - Kruskal works on disconnected forests naturally and uses Disjoint Set Union (DSU) to efficiently detect cycles.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Greedy Edge Sorting + Disjoint Set Union (DSU):
 *   1. Store all edges in an edge list `(u, v, weight)`.
 *   2. Sort the edge list in non-decreasing order of weights.
 *   3. Initialize DSU with `V` singleton sets.
 *   4. Iterate through sorted edges:
 *      - If `find(u) != find(v)`, the edge does NOT form a cycle:
 *        - Add edge weight to `mstWeight`.
 *        - Include edge in `mstEdges`.
 *        - `union(u, v)`.
 *      - If `find(u) == find(v)`, discard the edge (it creates a cycle).
 *   5. Stop early when `V - 1` edges are added.
 * 
 * TIME COMPLEXITY:
 * - O(E log E + E * alpha(V)): Dominated by sorting E edges.
 * 
 * SPACE COMPLEXITY:
 * - O(V + E) for DSU structures and edge list.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class DSU {
    std::vector<int> parent, rank;
public:
    DSU(int n) : parent(n), rank(n, 0) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int u) {
        if (parent[u] == u) return u;
        return parent[u] = find(parent[u]);
    }

    bool unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU == rootV) return false;

        if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
        return true;
    }
};

int kruskalMST(int V, std::vector<Edge>& edges, std::vector<Edge>& mstEdges) {
    // Sort all edges in ascending order of weights
    std::sort(edges.begin(), edges.end());

    DSU dsu(V);
    int mstCost = 0;
    int edgesCount = 0;

    for (const auto& edge : edges) {
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Only include an edge if its endpoints reside in different connected components (prevents cycle creation).
        if (dsu.unite(edge.u, edge.v)) {
            mstCost += edge.weight;
            mstEdges.push_back(edge);
            edgesCount++;
            if (edgesCount == V - 1) break; // MST complete
        }
    }

    return mstCost;
}

int main() {
    int V = 4;
    std::vector<Edge> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    std::vector<Edge> mstEdges;
    int totalCost = kruskalMST(V, edges, mstEdges);

    std::cout << "Kruskal's MST Total Cost: " << totalCost << "\n"; // Expected: 19
    std::cout << "Edges in MST:\n";
    for (const auto& e : mstEdges) {
        std::cout << e.u << " - " << e.v << " : " << e.weight << "\n";
    }

    return 0;
}
