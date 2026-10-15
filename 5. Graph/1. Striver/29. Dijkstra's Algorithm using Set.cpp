// Problem: Dijkstra's Algorithm (using Set)
// Link: https://www.geeksforgeeks.org/problems/implementing-dijkstra-set-1-adjacency-matrix/1
// Difficulty: Medium
// Topic: Graph, Shortest Path, Dijkstra's Algorithm, Greedy, Set, Red-Black Tree

/*
Problem Statement:
Given a weighted, undirected and connected graph of V vertices (0 to V-1) and an adjacency list adj, 
where adj[u] contains pairs of {v, weight} representing an edge between u and v with a given weight.

Given a source vertex src, find the shortest distance from the source vertex src to all other vertices.
Return a list of integers denoting the shortest distance from src to each vertex using std::set.

Example 1:
Input: V = 3, E = 3, src = 2
Edges:
0 - 1 (wt: 9)
0 - 2 (wt: 1)
1 - 2 (wt: 2)
Output: [1, 2, 0]
Explanation:
- Distance to 2 (src): 0
- Distance to 0: 2 -> 0 = 1
- Distance to 1: 2 -> 1 = 2

Example 2:
Input: V = 2, E = 1, src = 0
Edges: 0 - 1 (wt: 9)
Output: [0, 9]

Constraints:
- 1 <= V <= 10^5
- 0 <= weight <= 10^5
- 0 <= src < V
- Graph does not contain negative weight cycles.
*/

// Approach: Dijkstra's Algorithm using std::set
// 1. Why use Set instead of Priority Queue?
//    - `priority_queue` does not support deletion/decrease-key. When a shorter distance is found, 
//      it simply pushes the new pair, leaving the older, worse pair in the heap (lazy deletion).
//    - `std::set` allows us to explicitly ERASE the older, larger distance pair `{dist[adjNode], adjNode}`
//      before inserting the updated shorter distance `{newDist, adjNode}`.
//    - This prevents the algorithm from ever having to process redundant, outdated paths later!
// 2. Algorithm Steps:
//    Step 1: Initialize distance array `dist` with infinity (1e9), and `dist[src] = 0`.
//    Step 2: Initialize `set<pair<int, int>> st;` storing `{distance, node}`.
//            Insert `{0, src}` into `st`.
//    Step 3: While `st` is not empty:
//            - Extract the minimum distance element from the front: `auto it = st.begin();`
//            - Save `d = it->first`, `node = it->second`, then `st.erase(it);`
//            - For every neighbor `{adjNode, edgeWeight}` in `adj[node]`:
//              - If `d + edgeWeight < dist[adjNode]`:
//                * If `dist[adjNode] != 1e9` (an older distance is already in set):
//                  `st.erase({dist[adjNode], adjNode});` // Remove outdated entry
//                * Update `dist[adjNode] = d + edgeWeight;`
//                * Insert updated pair: `st.insert({dist[adjNode], adjNode});`
//    Step 4: Return `dist`.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to find the shortest distance of all vertices from the source vertex src using std::set.
    vector<int> dijkstra(int V, vector<vector<pair<int, int>>>& adj, int src) {
        // Set stores {distance, node} in ascending sorted order
        set<pair<int, int>> st;

        // Initialize distances to infinity
        const int INF = 1e9;
        vector<int> dist(V, INF);

        // Distance to source is 0
        dist[src] = 0;
        st.insert({0, src});

        while (!st.empty()) {
            // st.begin() always points to the element with minimum distance
            auto it = st.begin();
            int d = it->first;
            int node = it->second;
            st.erase(it);

            // Traverse all adjacent neighbors
            for (auto& edge : adj[node]) {
                int adjNode = edge.first;
                int edgeWeight = edge.second;

                // Relaxation condition
                if (d + edgeWeight < dist[adjNode]) {
                    // If adjNode was previously reached with a longer distance,
                    // erase that old entry from the set to avoid redundant future processing
                    if (dist[adjNode] != INF) {
                        st.erase({dist[adjNode], adjNode});
                    }

                    // Update distance and insert into set
                    dist[adjNode] = d + edgeWeight;
                    st.insert({dist[adjNode], adjNode});
                }
            }
        }

        return dist;
    }
};

/*
Time Complexity: O(E * log V)
- Extracting minimum element from set: at most V times -> O(V * log V).
- For each edge, we may perform an erase and an insert operation: each takes O(log V).
- Across all edges: O(E * log V).
- Total Time Complexity: O(E * log V).

Space Complexity: O(V + E)
- Distance array: O(V).
- Set: stores at most V unique nodes at any point (since duplicates are erased): O(V).
- Adjacency list: O(V + E).
- Overall Auxiliary Space: O(V + E).

Key Insights & Priority Queue vs. Set Trade-off:
1. Does `set` save time compared to `priority_queue`?
   - `set.erase()` takes O(log V) time to locate and delete the node from the Red-Black Tree.
   - `priority_queue` avoids the deletion cost during insertion by simply pushing the new pair 
     and skipping stale entries later in O(1).
   - Although `set` processes fewer total iterations by eliminating duplicates, `priority_queue` 
     is built on a contiguous array (vector) with much better CPU cache locality.
   - In practice, `priority_queue` is generally faster in competitive programming and interviews,
     while `set` is more memory-compact since it never holds duplicate node entries.
*/
