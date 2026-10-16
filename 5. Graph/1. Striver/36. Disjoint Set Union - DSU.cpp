// Problem: Disjoint Set Union (DSU) - Union by Rank & Union by Size with Path Compression
// Video: Striver G-46 (https://www.youtube.com/watch?v=aBxjDBC4M1U)
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/disjoint-set-union-find/1
// Difficulty: Medium
// Topic: Graph, Disjoint Set Union (DSU), Union-Find, Connected Components

/*
Concept & Overview:
Disjoint Set Union (DSU) / Union-Find is a data structure that tracks a set of elements partitioned 
into a number of disjoint (non-overlapping) subsets.

Why do we need Disjoint Set?
1. Dynamic Graphs:
   - Standard BFS/DFS answers "Are nodes u and v connected?" in O(V + E) time.
   - If edges are added dynamically one by one, running BFS/DFS repeatedly takes O(Q * (V + E)), 
     which is way too slow for large graphs.
   - Disjoint Set answers connectivity queries in almost constant time O(4 * alpha) ≈ O(1)!

2. Core Operations:
   - `findUPar(node)`: Finds the ultimate parent (root representative) of the set containing `node`.
     Uses **Path Compression** to point nodes directly to their ultimate parent, flattening the tree.
   - `unionByRank(u, v)`: Connects the trees of u and v by attaching the tree with smaller rank (depth)
     under the root of the tree with larger rank.
   - `unionBySize(u, v)`: Connects the trees by attaching the smaller component under the root of the 
     larger component. (Often preferred because `size[root]` directly tracks component size!).

Time Complexity:
- Both `findUPar` and `union` operate in O(4 * alpha) ≈ O(1) amortized time, where alpha is the 
  Inverse Ackermann function (alpha(N) <= 4 for all practical values of N <= 10^80).
*/

// Step-by-Step Walkthrough:
// 1. Initialization:
//    - `parent[i] = i`: Initially, each node is its own independent parent.
//    - `rank[i] = 0`: Initially, rank of every node is 0.
//    - `size[i] = 1`: Initially, size of every component is 1.
//    - Allocate `n + 1` size to handle both 0-indexed and 1-indexed graphs seamlessly.
// 2. Path Compression in `findUPar(node)`:
//    - If `node == parent[node]`, return `node`.
//    - Otherwise, recursively find root: `parent[node] = findUPar(parent[node])`.
//    - By assigning the result back to `parent[node]`, all intermediate nodes point directly
//      to the root, collapsing the tree depth to 1 for subsequent queries.
// 3. Union by Rank:
//    - Find ultimate parents: `ulp_u = findUPar(u)`, `ulp_v = findUPar(v)`.
//    - If `ulp_u == ulp_v`, they already belong to the same component -> return.
//    - If `rank[ulp_u] < rank[ulp_v]`: Attach `ulp_u` under `ulp_v` (`parent[ulp_u] = ulp_v`).
//    - If `rank[ulp_v] < rank[ulp_u]`: Attach `ulp_v` under `ulp_u` (`parent[ulp_v] = ulp_u`).
//    - If ranks are equal: Attach one to the other arbitrarily, and increment the winner's rank!
// 4. Union by Size:
//    - If `size[ulp_u] < size[ulp_v]`: Attach `ulp_u` to `ulp_v`, update `size[ulp_v] += size[ulp_u]`.
//    - Otherwise: Attach `ulp_v` to `ulp_u`, update `size[ulp_u] += size[ulp_v]`.

#include <bits/stdc++.h>
using namespace std;

// -----------------------------------------------------------------------------
// UNIVERSAL DISJOINT SET TEMPLATE (Copy & Paste for any DSU Problem)
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
        // Path compression step: flattens the tree directly to the ultimate root
        return parent[node] = findUPar(parent[node]);
    }

    // Union by Rank
    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return; // Already in the same component

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

    // Union by Size (Highly recommended when problem asks for component sizes)
    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return; // Already in the same component

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

// -----------------------------------------------------------------------------
// EXAMPLE USAGE / QUESTION DEMONSTRATION: Dynamic Connectivity
// -----------------------------------------------------------------------------
class Solution {
public:
    // Function to check if two nodes are connected
    bool isConnected(int u, int v, DisjointSet& ds) {
        return ds.findUPar(u) == ds.findUPar(v);
    }
};

int main() {
    // Demonstration on a graph with 7 nodes (1-indexed: 1 to 7)
    int n = 7;
    DisjointSet ds(n);

    // Adding edges to form components:
    // Component 1: {1, 2, 3}
    ds.unionByRank(1, 2);
    ds.unionByRank(2, 3);

    // Component 2: {4, 5, 6, 7}
    ds.unionByRank(4, 5);
    ds.unionByRank(6, 7);
    ds.unionByRank(5, 6);

    Solution solver;

    cout << "Testing Disjoint Set Union by Rank:\n";
    // Check if 3 and 7 are in the same component
    if (solver.isConnected(3, 7, ds)) {
        cout << "3 and 7 are in the same component.\n";
    } else {
        cout << "3 and 7 are in DIFFERENT components.\n"; // Expected
    }

    // Connect node 3 and 7
    cout << "\nAdding edge between 3 and 7...\n";
    ds.unionByRank(3, 7);

    // Check again
    if (solver.isConnected(3, 7, ds)) {
        cout << "3 and 7 are NOW in the SAME component!\n"; // Expected
    } else {
        cout << "3 and 7 are in DIFFERENT components.\n";
    }

    // ---------------------------------------------------------
    // Testing Union by Size on a new instance
    // ---------------------------------------------------------
    cout << "\n----------------------------------------\n";
    cout << "Testing Disjoint Set Union by Size:\n";
    DisjointSet dsSize(n);
    dsSize.unionBySize(1, 2);
    dsSize.unionBySize(2, 3);
    cout << "Size of component containing node 1: " << dsSize.size[dsSize.findUPar(1)] << " (Expected: 3)\n";

    dsSize.unionBySize(4, 5);
    dsSize.unionBySize(6, 7);
    dsSize.unionBySize(5, 6);
    cout << "Size of component containing node 5: " << dsSize.size[dsSize.findUPar(5)] << " (Expected: 4)\n";

    dsSize.unionBySize(3, 7);
    cout << "After merging 3 and 7, total component size: " << dsSize.size[dsSize.findUPar(1)] << " (Expected: 7)\n";

    return 0;
}

/*
Time Complexity:
- Initialization: O(N) to resize and initialize parent/rank/size arrays.
- `findUPar(node)`: O(4 * alpha) ≈ O(1) amortized due to Path Compression.
- `unionByRank(u, v)`: O(4 * alpha) ≈ O(1) amortized.
- `unionBySize(u, v)`: O(4 * alpha) ≈ O(1) amortized.
- Here, alpha(N) is the Inverse Ackermann function, which grows so slowly that 
  alpha(10^80) <= 4 (constant time for all practical purposes).

Space Complexity: O(N)
- `parent` array: O(N)
- `rank` array: O(N)
- `size` array: O(N)
- Overall Auxiliary Space: O(N).

Key Insights:
1. Why Path Compression is Essential:
   - Without path compression, unions can create a skewed tree (like a linked list) of depth O(N).
   - `parent[node] = findUPar(parent[node])` re-wires every visited node directly to the root, 
     flattening subsequent traversals.
2. Rank vs. Size:
   - Union by Rank keeps tree height minimal by attaching smaller height under larger height.
   - Union by Size attaches smaller component count under larger component count.
   - *Interview Tip:* `unionBySize` is generally preferred because many interview questions 
     (e.g., LeetCode 827: Making A Large Island, LeetCode 947: Most Stones Removed) require 
     tracking the size of the connected component.
3. 1-Based vs. 0-Based Safety:
   - Sizing arrays with `n + 1` safely supports both 0-indexed and 1-indexed problems without 
     off-by-one errors.
*/
