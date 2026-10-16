// Problem: 547. Number of Provinces (using Disjoint Set Union)
// Video: Striver G-48 (https://www.youtube.com/watch?v=ZGr5nxMGIZM)
// Link (LeetCode): https://leetcode.com/problems/number-of-provinces/
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/number-of-provinces/1
// Difficulty: Medium
// Topic: Graph, Disjoint Set Union (DSU), Connected Components, Matrix Traversal

/*
Problem Statement:
There are n cities. Some of them are connected, while some are not. If city a is connected 
directly with city b, and city b is connected directly with city c, then city a is connected 
indirectly with city c.

A province is a group of directly or indirectly connected cities and no other cities outside 
of the group.

You are given an n x n matrix `isConnected` (or adjacency matrix `adj` in GFG) where 
isConnected[i][j] = 1 if the ith city and the jth city are directly connected, and 
isConnected[i][j] = 0 otherwise.

Return the total number of provinces.

Example 1:
Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
Output: 2
Explanation:
- City 0 and City 1 are directly connected -> Form Province 1: {0, 1}
- City 2 is not connected to any other city -> Forms Province 2: {2}
Total number of provinces = 2.

Example 2:
Input: isConnected = [[1,0,0],[0,1,0],[0,0,1]]
Output: 3
Explanation:
No cities are connected to each other. Each city forms its own province: {0}, {1}, {2}.
Total number of provinces = 3.

Example 3:
Input: isConnected = [[1,1,1],[1,1,1],[1,1,1]]
Output: 1
Explanation:
All cities are connected directly and indirectly. All 3 cities form a single province: {0, 1, 2}.
Total number of provinces = 1.

Constraints:
- 1 <= n <= 200
- n == isConnected.length == isConnected[i].length
- isConnected[i][j] is 1 or 0.
- isConnected[i][i] == 1
- isConnected[i][j] == isConnected[j][i]
*/

// Approach: Disjoint Set Union (DSU)
//
// Intuition:
// - A "province" is mathematically a "connected component" of an undirected graph.
// - In earlier questions (e.g., G-7 / G-8), we solved this using standard DFS / BFS traversals.
// - In this question, we solve it using DISJOINT SET UNION (DSU).
// - Why DSU?
//   1. DSU is uniquely designed for dynamic connectivity and grouping elements into disjoint sets.
//   2. It demonstrates how to translate an adjacency matrix into DSU union operations.
//   3. It forms the core conceptual bridge for advanced DSU problems (e.g., Number of Islands II,
//      Making A Large Island, Most Stones Removed).
//
// Step-by-Step Algorithm:
// Step 1: Initialize a Disjoint Set for `n` nodes (`DisjointSet ds(n)`).
//         Initially, every city `0` to `n-1` is in its own isolated set (`parent[i] = i`).
// Step 2: Iterate through the upper triangle of the adjacency matrix (`i` from 0 to n-1, `j` from i+1 to n-1):
//         - We only need to check `j > i` because the graph is undirected (`isConnected[i][j] == isConnected[j][i]`),
//           and self-loops `isConnected[i][i] == 1` do not connect distinct cities.
//         - If `isConnected[i][j] == 1`:
//           Perform `ds.unionBySize(i, j)` (or `unionByRank(i, j)`).
//           This merges the components containing city `i` and city `j`.
// Step 3: Count the number of provinces:
//         - Method A (Root Counting - Striver's Primary Approach):
//           A province is uniquely represented by its ultimate parent (root of tree).
//           Iterate through all cities `i` from 0 to n-1:
//           If `ds.parent[i] == i` (or `ds.findUPar(i) == i`), it is the representative root of a province.
//           Increment `provinceCount`.
//         - Method B (Dynamic Component Counter):
//           Start with `provinceCount = n`.
//           Every time `ds.unionBySize(u, v)` successfully merges two different components,
//           decrement `provinceCount--`.

#include <bits/stdc++.h>
using namespace std;

// -----------------------------------------------------------------------------
// UNIVERSAL DISJOINT SET TEMPLATE (Union by Rank & Union by Size)
// -----------------------------------------------------------------------------
class DisjointSet {
public:
    vector<int> rank, parent, size;

    // Constructor: n + 1 accommodates both 0-based and 1-based indexing
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
        }
    }

    // Find Ultimate Parent with Path Compression
    int findUPar(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }

    // Union by Rank: Returns true if two disjoint components were merged, false if already in same component
    bool unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return false;

        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        }
        else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        }
        else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
        return true;
    }

    // Union by Size (Preferred): Returns true if merged, false if already connected
    bool unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return false;

        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
        return true;
    }
};

// -----------------------------------------------------------------------------
// SOLUTION CLASS
// -----------------------------------------------------------------------------
class Solution {
public:
    // Approach 1: LeetCode 547 - Counting Ultimate Parents (Striver's standard method)
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        DisjointSet ds(n);

        // Step 1: Connect cities that have an edge between them
        // Check only upper triangle (j > i) to avoid redundant duplicate checks
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (isConnected[i][j] == 1) {
                    ds.unionBySize(i, j);
                }
            }
        }

        // Step 2: Count unique ultimate parents
        // A node `i` is the ultimate parent of its component iff parent[i] == i
        int provinces = 0;
        for (int i = 0; i < n; i++) {
            if (ds.parent[i] == i) {
                provinces++;
            }
        }

        return provinces;
    }

    // Approach 2: Dynamic Component Decrement (Optimization)
    // Starts with n components and decrements on each successful union
    int findCircleNumOptimized(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        DisjointSet ds(n);
        int components = n; // Initially each node is its own component

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (isConnected[i][j] == 1) {
                    // If union successfully connects two distinct components, decrement count
                    if (ds.unionBySize(i, j)) {
                        components--;
                    }
                }
            }
        }

        return components;
    }

    // Approach 3: GFG Signature: numProvinces(adj, V)
    int numProvinces(vector<vector<int>> adj, int V) {
        DisjointSet ds(V);

        for (int i = 0; i < V; i++) {
            for (int j = i + 1; j < V; j++) {
                if (adj[i][j] == 1) {
                    ds.unionBySize(i, j);
                }
            }
        }

        int count = 0;
        for (int i = 0; i < V; i++) {
            if (ds.parent[i] == i) {
                count++;
            }
        }
        return count;
    }
};

// -----------------------------------------------------------------------------
// DRIVER CODE / DEMONSTRATION
// -----------------------------------------------------------------------------
int main() {
    Solution solver;

    cout << "===================================================================\n";
    cout << "          547. NUMBER OF PROVINCES (DISJOINT SET UNION)            \n";
    cout << "===================================================================\n";

    // -------------------------------------------------------------------------
    // TEST CASE 1: Two provinces {0, 1} and {2}
    // -------------------------------------------------------------------------
    cout << "\n[TEST CASE 1]\n";
    vector<vector<int>> isConnected1 = {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 1}
    };
    int ans1 = solver.findCircleNum(isConnected1);
    int ans1_opt = solver.findCircleNumOptimized(isConnected1);
    cout << "Input Matrix:\n";
    cout << "  [1, 1, 0]\n  [1, 1, 0]\n  [0, 0, 1]\n";
    cout << "Provinces (Root Counting)      : " << ans1 << " (Expected: 2)\n";
    cout << "Provinces (Dynamic Decrement)  : " << ans1_opt << " (Expected: 2)\n";

    // -------------------------------------------------------------------------
    // TEST CASE 2: Three isolated provinces {0}, {1}, {2}
    // -------------------------------------------------------------------------
    cout << "\n-------------------------------------------------------------------\n";
    cout << "[TEST CASE 2]\n";
    vector<vector<int>> isConnected2 = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    int ans2 = solver.findCircleNum(isConnected2);
    int ans2_opt = solver.findCircleNumOptimized(isConnected2);
    cout << "Input Matrix:\n";
    cout << "  [1, 0, 0]\n  [0, 1, 0]\n  [0, 0, 1]\n";
    cout << "Provinces (Root Counting)      : " << ans2 << " (Expected: 3)\n";
    cout << "Provinces (Dynamic Decrement)  : " << ans2_opt << " (Expected: 3)\n";

    // -------------------------------------------------------------------------
    // TEST CASE 3: Single fully connected province {0, 1, 2, 3}
    // -------------------------------------------------------------------------
    cout << "\n-------------------------------------------------------------------\n";
    cout << "[TEST CASE 3]\n";
    vector<vector<int>> isConnected3 = {
        {1, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 1, 1, 1},
        {0, 0, 1, 1}
    };
    int ans3 = solver.findCircleNum(isConnected3);
    int ans3_opt = solver.findCircleNumOptimized(isConnected3);
    cout << "Input Matrix: 4-city line graph (0-1-2-3)\n";
    cout << "Provinces (Root Counting)      : " << ans3 << " (Expected: 1)\n";
    cout << "Provinces (Dynamic Decrement)  : " << ans3_opt << " (Expected: 1)\n";

    return 0;
}

/*
================================================================================
COMPLEXITY ANALYSIS:
================================================================================
1. Time Complexity:
   - Nested loops inspect the upper triangle of the n x n matrix:
     Number of pairs inspected = n * (n - 1) / 2 = O(n^2).
   - For each connected pair (i, j), we call `unionBySize(i, j)`.
   - Each DSU operation with path compression and union by size takes O(4 * alpha) ≈ O(1) amortized time,
     where alpha is the Inverse Ackermann function.
   - Final loop to count ultimate parents takes O(n) time.
   - Total Time Complexity: O(n^2 * alpha) + O(n) ≈ O(n^2).

2. Space Complexity:
   - Disjoint Set arrays:
     * `parent` array of size (n + 1): O(n)
     * `size` array of size (n + 1): O(n)
     * `rank` array of size (n + 1): O(n)
   - Total Space Complexity: O(n) auxiliary space.

================================================================================
KEY INSIGHTS & INTERVIEW TAKEAWAYS:
================================================================================
1. DFS / BFS vs. Disjoint Set Union (DSU):
   - DFS / BFS:
     * Excellent for static graphs where all edges are fixed upfront.
     * Takes O(V^2) for adjacency matrix, O(V + E) for adjacency list.
     * Requires recursion stack (DFS) or queue (BFS) of size O(V).
   - Disjoint Set Union (DSU):
     * Ideal when edges are added dynamically one by one over time.
     * No recursion stack during traversal (tree depth remains <= 4 due to path compression).
     * Easy to maintain additional component metadata (e.g., component size, max element).

2. Root Counting vs. Dynamic Decrement:
   - Root Counting (`parent[i] == i`): Clean, decoupled from the union process.
     Notice that we can directly check `parent[i] == i` because the root of any DSU tree 
     always satisfies `parent[root] == root`.
   - Dynamic Decrement: Starts with `n` components and decrements on each successful union.
     Avoids the final O(n) loop altogether.

3. Upper Triangle Matrix Optimization:
   - Since `isConnected[i][j] == isConnected[j][i]` and `isConnected[i][i] == 1`, 
     we only need to iterate over `j > i`. This cuts the number of operations in half 
     from n^2 to n*(n-1)/2.
*/
