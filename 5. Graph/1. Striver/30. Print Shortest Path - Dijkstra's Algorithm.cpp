// Problem: Print Shortest Path (Dijkstra's Algorithm)
// Link (GFG): https://www.geeksforgeeks.org/problems/shortest-path-in-weighted-undirected-graph/1
// Difficulty: Medium
// Topic: Graph, Dijkstra's Algorithm, Shortest Path, Priority Queue, Parent Tracking, Backtracking

/*
Problem Statement:
You are given a weighted undirected graph having n vertices numbered from 1 to n and m edges along with their weights.
Find the shortest path from vertex 1 to vertex n.

Return format (Modern GFG):
- A list of integers where the first element is the total weight/distance of the shortest path, 
  followed by the nodes visited along the path from 1 to n: {total_weight, 1, ..., n}.
- If no path exists from 1 to n, return {-1}.

(Note: Classic format returns only the path vertices: {1, ..., n}).

Example 1:
Input: n = 5, m = 6
edges = [[1, 2, 2], [2, 5, 5], [2, 3, 4], [1, 4, 1], [4, 3, 3], [3, 5, 1]]
Output: [5, 1, 4, 3, 5]
Explanation:
Shortest path from 1 to 5:
1 -> 4 (wt 1) -> 3 (wt 3) -> 5 (wt 1) = Total distance 5.
Path nodes: 1 -> 4 -> 3 -> 5.

Example 2:
Input: n = 2, m = 1
edges = [[1, 2, 2]]
Output: [2, 1, 2]

Example 3:
Input: n = 3, m = 1
edges = [[1, 2, 5]]
Output: [-1]
Explanation: Vertex 3 cannot be reached from vertex 1.

Constraints:
- 2 <= n <= 10^5
- 0 <= m <= 10^5
- 1 <= u, v <= n
- 1 <= weight <= 10^5
*/

// Approach: Dijkstra's Algorithm with Parent Array Tracking
// 1. Core Intuition:
//    - Standard Dijkstra only finds the minimum distance to each node, but not the path.
//    - To reconstruct the actual path, maintain a `parent` array:
//      * parent[i] stores the node from which vertex `i` was relaxed to achieve its shortest distance.
//    - Initially, each node is its own parent: parent[i] = i.
//    - When an edge u -> v relaxes dist[v]:
//      dist[v] = d + weight;
//      parent[v] = u; // Record that u is the predecessor of v on the shortest path!
// 2. Backtracking the Path:
//    - After Dijkstra completes:
//      * If dist[n] == 1e9, vertex n is unreachable -> return {-1}.
//      * Otherwise, start from node `n` and backtrack:
//        int curr = n;
//        while (parent[curr] != curr) {
//            path.push_back(curr);
//            curr = parent[curr];
//        }
//        path.push_back(1); // Source vertex
//    - Reverse the path vector to obtain the order from 1 to n.
// 3. Output Preparation:
//    - Prepend dist[n] to the path as required by GFG: {dist[n], 1, ..., n}.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> shortestPath(int n, int m, vector<vector<int>>& edges) {
        // Step 1: Build adjacency list (1-indexed graph)
        vector<vector<pair<int, int>>> adj(n + 1);
        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        // Step 2: Initialize distance and parent arrays
        const int INF = 1e9;
        vector<int> dist(n + 1, INF);
        vector<int> parent(n + 1);
        for (int i = 1; i <= n; i++) {
            parent[i] = i; // Every node is initially its own parent
        }

        // Min-heap storing {distance, node}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        dist[1] = 0;
        pq.push({0, 1});

        // Step 3: Run Dijkstra's Algorithm
        while (!pq.empty()) {
            auto [d, node] = pq.top();
            pq.pop();

            if (d > dist[node]) continue;

            for (auto& edge : adj[node]) {
                int adjNode = edge.first;
                int edgeWeight = edge.second;

                // Relaxation step
                if (d + edgeWeight < dist[adjNode]) {
                    dist[adjNode] = d + edgeWeight;
                    pq.push({dist[adjNode], adjNode});
                    parent[adjNode] = node; // Track the parent
                }
            }
        }

        // Step 4: If destination node 'n' is unreachable
        if (dist[n] == INF) {
            return {-1};
        }

        // Step 5: Backtrack from node 'n' to node 1 using the parent array
        vector<int> path;
        int curr = n;
        while (parent[curr] != curr) {
            path.push_back(curr);
            curr = parent[curr];
        }
        path.push_back(1); // Add the source node

        // Reverse to get path from 1 to n
        reverse(path.begin(), path.end());

        // Step 6: Construct result {total_weight, 1, ..., n}
        vector<int> result;
        result.push_back(dist[n]); // Total shortest path weight
        for (int node : path) {
            result.push_back(node);
        }

        return result;
    }
};

/*
Time Complexity: O(E * log V + V)
- Building the adjacency list: O(E).
- Dijkstra's Algorithm: O(E * log V).
- Path Reconstruction: backtracking from node n to 1 takes at most O(V) time.
- Reversing the path: O(V).
- Overall Time Complexity: O(E * log V).

Space Complexity: O(V + E)
- Adjacency list: O(V + E).
- Distance array: O(V).
- Parent array: O(V).
- Priority queue: O(V).
- Path vector: O(V).
- Overall Auxiliary Space: O(V + E).

Key Insights:
1. The Parent Array Concept:
   - Dijkstra only maintains the running shortest distance to each node.
   - Recording `parent[adjNode] = node` whenever relaxation occurs creates a predecessor tree
     rooted at the source vertex.
2. Backtracking from Destination to Source:
   - Since each node stores its single unique predecessor on its shortest path, we can follow 
     pointers backwards from `n` until we reach a node where `parent[curr] == curr` (the source).
   - Reversing this sequence gives the forward shortest path.
3. Multiple Shortest Paths:
   - If multiple paths have the same minimum total weight, the algorithm will naturally output 
     one valid path based on which edge was relaxed last.
*/
