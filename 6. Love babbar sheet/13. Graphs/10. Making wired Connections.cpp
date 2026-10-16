/**
 * Problem: Number of Operations to Make Network Connected (Making Wired Connections)
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Simple connectivity checks determine if a graph is fully connected.
 * - Here, we are given a fixed pool of existing cables (edges) that we can disconnect and reroute.
 * - We need to determine if we have enough spare cables to bridge all disconnected components, and if so, how many moves are required.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Disjoint Set Union (DSU) / Connected Components:
 *   1. Fundamental graph theorem: Connecting `n` nodes requires at least `n - 1` edges.
 *      If `connections.size() < n - 1`, it is physically impossible; return `-1`.
 *   2. If `connections.size() >= n - 1`, we are guaranteed to have enough redundant edges.
 *   3. Count the number of connected components `C` using DSU or DFS.
 *   4. To connect `C` independent components into a single spanning forest, we need exactly `C - 1` cables.
 * 
 * TIME COMPLEXITY:
 * - O(V + E * alpha(V)) using DSU with path compression and union by rank.
 * 
 * SPACE COMPLEXITY:
 * - O(V) for the parent and rank arrays.
 */

#include <iostream>
#include <vector>
#include <numeric>

class DisjointSet {
    std::vector<int> parent, rank;
public:
    int components;

    DisjointSet(int n) : parent(n), rank(n, 0), components(n) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int u) {
        if (parent[u] == u) return u;
        return parent[u] = find(parent[u]); // Path compression
    }

    bool unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU == rootV) return false; // Redundant edge / cycle

        // Union by rank
        if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
        components--;
        return true;
    }
};

int makeConnected(int n, std::vector<std::vector<int>>& connections) {
    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // A connected graph with n nodes requires at least n - 1 edges; if fewer, connection is impossible.
    if ((int)connections.size() < n - 1) return -1;

    DisjointSet dsu(n);
    for (const auto& conn : connections) {
        dsu.unite(conn[0], conn[1]);
    }

    // Number of cables needed to connect 'C' independent components is C - 1
    return dsu.components - 1;
}

int main() {
    int n = 6;
    std::vector<std::vector<int>> connections = {
        {0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}
    };

    int result = makeConnected(n, connections);
    std::cout << "Minimum operations to make network connected: " << result << "\n"; // Expected: 2

    return 0;
}
