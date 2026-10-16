// Problem: Kruskal's Algorithm - Minimum Spanning Tree (MST)
// Video: Striver G-47 (https://www.youtube.com/watch?v=DMnDM_sxVig)
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/minimum-spanning-tree/1
// Link (LeetCode Reference): https://leetcode.com/problems/min-cost-to-connect-all-points/
// Difficulty: Medium
// Topic: Graph, Minimum Spanning Tree (MST), Disjoint Set Union (DSU), Greedy, Sorting

/*
Problem Statement:
Given a weighted, undirected, and connected graph of V vertices and E edges, represented either as:
1. An adjacency list `adj` where adj[u] contains pairs {v, weight} representing an edge between u and v, or
2. A list of edges `[u, v, weight]`.

Find the sum of the weights of the edges in the Minimum Spanning Tree (MST) of the graph.
Additionally, determine and display the exact edges that comprise the MST.

What is a Spanning Tree?
A spanning tree of an undirected graph G is a subgraph that:
1. Contains ALL vertices of graph G (V vertices).
2. Is connected and acyclic (contains no cycles).
3. Has exactly (V - 1) edges.

What is a Minimum Spanning Tree (MST)?
Among all possible spanning trees of a weighted graph, the Minimum Spanning Tree is the one 
with the MINIMUM total edge weight sum.

Example 1:
Input: V = 5, E = 6
Edges:
0 - 1 (wt: 2)
0 - 2 (wt: 1)
1 - 2 (wt: 1)
2 - 3 (wt: 2)
3 - 4 (wt: 1)
4 - 2 (wt: 2)

Output: 5
Explanation:
The edges included in the MST are:
- (0, 2) with weight 1
- (1, 2) with weight 1
- (3, 4) with weight 1
- (2, 3) with weight 2
Total MST Weight = 1 + 1 + 1 + 2 = 5.
Notice:
- Edge (0, 1) of weight 2 is REJECTED because nodes 0 and 1 are already connected via node 2 (would form cycle 0-1-2-0).
- Edge (4, 2) of weight 2 is REJECTED because nodes 4 and 2 are already connected via node 3 (would form cycle 2-3-4-2).

Example 2:
Input: V = 4, E = 5
Edges:
0 - 1 (wt: 10)
0 - 2 (wt: 6)
0 - 3 (wt: 5)
1 - 3 (wt: 15)
2 - 3 (wt: 4)

Output: 19
Explanation:
Sorted edges by weight:
1. (2, 3, wt: 4)  -> TAKEN    (Components: {2, 3}, {0}, {1}) | Total wt = 4
2. (0, 3, wt: 5)  -> TAKEN    (Components: {0, 2, 3}, {1})    | Total wt = 9
3. (0, 2, wt: 6)  -> REJECTED (0 and 2 already in same component -> Cycle!)
4. (0, 1, wt: 10) -> TAKEN    (Components: {0, 1, 2, 3})      | Total wt = 19
5. (1, 3, wt: 15) -> REJECTED (1 and 3 already in same component -> Cycle!)
Total MST Weight = 19 with 3 edges: {(2, 3), (0, 3), (0, 1)}.

Constraints:
- 1 <= V <= 10^5
- 1 <= E <= 2 * 10^5
- 1 <= weight <= 10^5
- Graph is connected and undirected.
*/

// Approach: Kruskal's Algorithm using Disjoint Set Union (DSU)
//
// Intuition:
// - Kruskal's algorithm is a GREEDY strategy that constructs the MST edge by edge.
// - To achieve minimal total weight, we should always prefer edges with the smallest possible weight.
// - However, an edge cannot be added if it connects two vertices that are already part of the same 
//   connected component, as doing so would introduce a cycle.
// - How do we check if two vertices are in the same component and merge them in almost O(1) time?
//   -> Use DISJOINT SET UNION (DSU) with Path Compression and Union by Size/Rank!
//
// Step-by-Step Algorithm:
// Step 1: Extract all edges from the graph representation into a unified list of tuples: `{weight, u, v}`.
//         For an undirected adjacency list, we can extract each edge once (e.g. only when u < v).
// Step 2: Sort all edges in non-decreasing (ascending) order of their weight.
// Step 3: Initialize a Disjoint Set data structure with V vertices (`DisjointSet ds(V)`).
// Step 4: Initialize `mstWeight = 0`, `mstEdges` list, and `edgeCount = 0`.
// Step 5: Iterate through the sorted edges `{wt, u, v}`:
//         - Check if `u` and `v` belong to different components:
//           `if (ds.findUPar(u) != ds.findUPar(v))`
//           * Add `wt` to `mstWeight`.
//           * Add edge `{u, v}` to `mstEdges`.
//           * Merge the components: `ds.unionBySize(u, v)` (or `unionByRank`).
//           * Increment `edgeCount`.
//           * Optimization: If `edgeCount == V - 1`, the MST is complete! We can terminate early.
//         - Else:
//           * Skip this edge because adding it would form a cycle.
// Step 6: Return `mstWeight` (and optionally `mstEdges`).

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
        // Path compression flattens the tree directly to the ultimate root
        return parent[node] = findUPar(parent[node]);
    }

    // Union by Rank
    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;

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
    }

    // Union by Size (Preferred)
    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;

        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

// Custom Edge structure for readability and sorting
struct Edge {
    int u;
    int v;
    int wt;

    // Comparator to sort edges in non-decreasing order of weight
    bool operator<(const Edge& other) const {
        return wt < other.wt;
    }
};

// -----------------------------------------------------------------------------
// SOLUTION CLASS
// -----------------------------------------------------------------------------
class Solution {
public:
    // 1. Standard GFG Signature: Adjacency list representation
    // adj[u] = list of {v, weight}
    int spanningTree(int V, vector<vector<int>> adj[]) {
        // Step 1: Extract all unique undirected edges
        // Using tuple: {wt, u, v}
        vector<pair<int, pair<int, int>>> edges;
        
        for (int u = 0; u < V; u++) {
            for (auto& neighbor : adj[u]) {
                int v = neighbor[0];
                int wt = neighbor[1];
                // Since graph is undirected, only add (u, v) once when u < v
                // to avoid processing duplicate opposite edges
                if (u < v) {
                    edges.push_back({wt, {u, v}});
                }
            }
        }

        // Step 2: Sort all edges by weight in ascending order
        sort(edges.begin(), edges.end());

        // Step 3: Initialize Disjoint Set for V vertices
        DisjointSet ds(V);
        int mstWeight = 0;
        int edgesCount = 0;

        // Step 4 & 5: Process edges greedily
        for (auto& it : edges) {
            int wt = it.first;
            int u = it.second.first;
            int v = it.second.second;

            // Check if u and v are in different components
            if (ds.findUPar(u) != ds.findUPar(v)) {
                mstWeight += wt;
                ds.unionBySize(u, v);
                edgesCount++;

                // Early exit: A spanning tree on V vertices always has exactly V - 1 edges
                if (edgesCount == V - 1) {
                    break;
                }
            }
        }

        return mstWeight;
    }

};


/*
================================================================================
COMPLEXITY ANALYSIS:
================================================================================
1. Time Complexity:
   - Extracting Edges from Adjacency List: O(V + 2E) = O(V + E)
   - Sorting all E edges: O(E * log(E))
   - DSU Operations (Find & Union):
     * For each of the E edges, we call `findUPar` twice and `unionBySize` at most once.
     * Each DSU operation takes O(4 * alpha) ≈ O(1) amortized time, where alpha is the 
       Inverse Ackermann function (alpha <= 4 for all practical values of V).
     * Total DSU time: O(E * 4 * alpha) ≈ O(E)
   - Overall Time Complexity: O(E * log(E)) + O(E * 4 * alpha) ≈ O(E * log(E))
     Note: Since E <= V^2 in simple graphs, log(E) <= log(V^2) = 2 * log(V).
     Therefore, O(E * log(E)) is asymptotically equivalent to O(E * log(V)).

2. Space Complexity:
   - Edge list storage: O(E) to hold all edges.
   - Disjoint Set arrays:
     * `parent` array: O(V)
     * `rank` or `size` array: O(V)
   - MST edges vector: O(V - 1) = O(V)
   - Overall Space Complexity: O(V + E) auxiliary space.

================================================================================
KEY INSIGHTS & INTERVIEW TAKEAWAYS:
================================================================================
1. Kruskal's vs. Prim's Algorithm:
   -------------------------------------------------------------------------
   Feature             | Kruskal's Algorithm          | Prim's Algorithm
   -------------------------------------------------------------------------
   Philosophy          | Edge-centric (Greedy)        | Vertex-centric (Greedy)
   Data Structure      | Disjoint Set Union (DSU)     | Priority Queue (Min-Heap)
   Edge Sorting        | Sorts ALL edges upfront      | Explores adjacent edges on the fly
   Time Complexity     | O(E log E) or O(E log V)     | O(E log V)
   Best suited for     | Sparse Graphs (E ≈ V)        | Dense Graphs (E ≈ V^2)
   Disconnected Graph  | Finds Minimum Spanning Forest| Requires running per component
   -------------------------------------------------------------------------

2. Cycle Detection via DSU:
   - DSU enables dynamic connectivity checks in nearly O(1) time.
   - Two vertices `u` and `v` have the same ultimate parent `findUPar(u) == findUPar(v)`
     if and only if there already exists a path connecting them in the current spanning forest.
   - Hence, checking `findUPar(u) != findUPar(v)` strictly prevents cycle formation.

3. Early Termination Optimization:
   - Any valid spanning tree of V vertices contains EXACTLY (V - 1) edges.
   - By breaking out of the loop once `edgesCount == V - 1`, we avoid checking the 
     remaining larger edges, yielding significant runtime improvements on dense graphs.

4. Graph Disconnectedness / Forest:
   - If after processing all edges the number of edges picked is < V - 1, the graph is 
     disconnected. In that case, Kruskal's algorithm naturally constructs a 
     "Minimum Spanning Forest" across all components.
*/
