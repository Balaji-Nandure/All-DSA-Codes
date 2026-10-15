// Problem: Dijkstra's Algorithm (using Priority Queue)
// Link: https://www.geeksforgeeks.org/problems/implementing-dijkstra-set-1-adjacency-matrix/1
// Difficulty: Medium
// Topic: Graph, Shortest Path, Dijkstra's Algorithm, Greedy, Priority Queue, Min-Heap

/*
Problem Statement:
Given a weighted, undirected and connected graph of V vertices (0 to V-1) and an adjacency list adj, 
where adj[u] contains pairs of {v, weight} representing an edge between u and v with a given weight.

Given a source vertex src, find the shortest distance from the source vertex src to all other vertices.
Return a list of integers denoting the shortest distance from src to each vertex.

Example 1:
Input: V = 3, E = 3, src = 2
Edges:
0 - 1 (wt: 9)
0 - 2 (wt: 1)
1 - 2 (wt: 2)
Output: [4, 3, 0] // (or [1, 2, 0] depending on 2->0=1, 2->1=2, 2->2=0)
Explanation:
- Distance to 2 (src): 0
- Distance to 0: 2 -> 0 = 1
- Distance to 1: 2 -> 1 = 2 (or 2 -> 0 -> 1 = 1 + 9 = 10, min is 2)

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

// Approach: Dijkstra's Algorithm using Min-Heap (Priority Queue)
// 1. Why Dijkstra?
//    - Single-source shortest path algorithm for graphs with NON-NEGATIVE edge weights.
//    - Greedily selects the node with the smallest tentative distance at each step.
// 2. Why Min-Heap?
//    - A normal Queue (like in BFS) processes in FIFO order, which works ONLY when edge weights are uniform (1).
//    - In a weighted graph, a min-heap ensures we ALWAYS explore the least costly path next.
// 3. Algorithm Steps:
//    Step 1: Initialize distance array `dist` with infinity (1e9), and set `dist[src] = 0`.
//    Step 2: Initialize a min-heap storing pairs `{distance, node}`:
//            `priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;`
//            Push `{0, src}` into pq.
//    Step 3: While pq is not empty:
//            - Extract the top element: `auto [d, node] = pq.top(); pq.pop();`
//            - Optimization: If `d > dist[node]`, skip it (stale entry already updated with a shorter path).
//            - For every neighbor `{adjNode, edgeWeight}` in `adj[node]`:
//              - If `d + edgeWeight < dist[adjNode]`:
//                * `dist[adjNode] = d + edgeWeight;`
//                * `pq.push({dist[adjNode], adjNode});`
//    Step 4: Return `dist`.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to find the shortest distance of all vertices from the source vertex src.
    vector<int> dijkstra(int V, vector<vector<pair<int, int>>>& adj, int src) {
        // -------------------------------------------------------------------------
        // DATA STRUCTURE CHOICE EXPLANATION:
        // 1. Why `priority_queue` (min-heap) instead of `queue`?
        //    - In graphs with non-uniform edge weights, a path with fewer edges may have a 
        //      much higher total weight than a path with more edges.
        //    - A FIFO queue would explore by edge count, NOT by cheapest distance.
        //    - A min-heap ensures we ALWAYS expand the globally closest unvisited node first.
        //
        // 2. Why `greater<pair<int, int>>`?
        //    - By default, C++ `priority_queue` is a MAX-HEAP (pops the largest element).
        //    - `greater<...>` flips it into a MIN-HEAP (pops the smallest element).
        //
        // 3. Why store `{distance, node}` instead of `{node, distance}`?
        //    - In C++, `std::pair` comparison compares the first element first (`d`).
        //    - Putting `distance` first ensures the min-heap automatically sorts by minimum
        //      distance without writing a custom comparator class!
        // -------------------------------------------------------------------------
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // Initialize distances to infinity
        const int INF = 1e9;
        vector<int> dist(V, INF);

        // Distance from source to itself is always 0
        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            auto [d, node] = pq.top();
            pq.pop();

            // Optimization: If popped distance is greater than recorded shortest distance, skip
            if (d > dist[node]) continue;

            // Traverse all adjacent neighbors of current node
            for (auto& edge : adj[node]) {
                int adjNode = edge.first;
                int edgeWeight = edge.second;

                // Relaxation step
                if (d + edgeWeight < dist[adjNode]) {
                    dist[adjNode] = d + edgeWeight;
                    pq.push({dist[adjNode], adjNode});
                }
            }
        }

        return dist;
    }
};

/*
Time Complexity: O(E * log V)
- In the worst case, every edge relaxation results in pushing a new entry into the priority queue: at most E pushes.
- Size of priority queue is at most V (or E in dense cases).
- Each pop and push operation on the min-heap takes O(log V).
- Total Time Complexity: O(E * log V) where E is the number of edges and V is the number of vertices.

Space Complexity: O(V + E)
- Distance array: O(V).
- Min-heap (Priority Queue): O(V) (or O(E) with unrelaxed duplicate entries).
- Adjacency list: O(V + E).
- Overall Auxiliary Space: O(V + E).

Key Insights:
1. Why store {distance, node} instead of {node, distance}?
   - C++ std::pair compares the first element by default. Putting `distance` first avoids writing 
     a custom comparator for the min-heap.
2. Why does Dijkstra fail for Negative Weights / Negative Cycles?
   - Dijkstra assumes that once a node is popped from the min-heap, its shortest distance is finalized.
   - A negative edge weight can decrease the distance even after a node was marked finalized, 
     violating Dijkstra's greedy assumption. For negative weights, Bellman-Ford algorithm must be used.
3. The Stale Entry Check (`if (d > dist[node]) continue`):
   - In C++, std::priority_queue does not support a `decrease_key` operation.
   - When a shorter path to a node is discovered, we push a new `{new_dist, node}` into the heap.
   - The older, longer distance remains in the heap. Checking `if (d > dist[node]) continue;` 
     skips these stale entries in O(1) time when they are later popped.
*/
