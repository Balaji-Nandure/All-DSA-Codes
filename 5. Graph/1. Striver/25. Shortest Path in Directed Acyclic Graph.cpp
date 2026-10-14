// Problem: Shortest Path in Directed Acyclic Graph (DAG)
// Link: https://www.geeksforgeeks.org/problems/shortest-path-in-undirected-graph/1
// Difficulty: Medium
// Topic: Graph, DAG, Topological Sort, DFS, Shortest Path, Edge Relaxation

/*
Problem Statement:
Given a Directed Acyclic Graph (DAG) of N vertices from 0 to N-1 and M edges, 
where each edge has a weight, find the shortest path from the source vertex (vertex 0) 
to all other vertices. 

If a vertex is unreachable from the source, its distance should be marked as -1.

Example 1:
Input: N = 6, M = 7
edges = {{0,1,2}, {0,4,1}, {4,5,4}, {4,2,2}, {1,2,3}, {2,3,6}, {5,3,1}}
Output: [0, 2, 3, 6, 1, 5]
Explanation:
Shortest paths from source 0:
- To 0: 0
- To 1: 0 -> 1 = 2
- To 2: 0 -> 4 -> 2 = 1 + 2 = 3
- To 3: 0 -> 4 -> 5 -> 3 = 1 + 4 + 1 = 6
- To 4: 0 -> 4 = 1
- To 5: 0 -> 4 -> 5 = 1 + 4 = 5

Example 2:
Input: N = 4, M = 2
edges = {{0,1,2}, {0,2,1}}
Output: [0, 2, 1, -1]
Explanation: Vertex 3 is unreachable from 0, so its distance is -1.

Constraints:
- 1 <= N <= 100
- 1 <= M <= min(N*(N-1), 1000)
- 0 <= edge[i][0], edge[i][1] < N
- 0 <= edge[i][2] <= 100
*/

// Approach: Topological Sort + Edge Relaxation (Linear Time Shortest Path)
// 1. Why not Dijkstra?
//    - Dijkstra's algorithm takes O((V + E) log V).
//    - In a DAG (no cycles), Topological Sort guarantees that we process all dependencies of a node
//      BEFORE we process the node itself.
//    - This allows us to find single-source shortest paths in strictly linear O(V + E) time!
//    - Works even with negative edge weights (since DAGs cannot have negative cycles).
// 2. Algorithm Steps:
//    Step 1: Build the weighted adjacency list: adj[u].push_back({v, wt}).
//    Step 2: Find the Topological Sort order using DFS with a stack.
//    Step 3: Initialize distance array: dist[i] = 1e9, dist[0] = 0 (source is 0).
//    Step 4: Pop nodes from the stack one by one:
//            - If dist[node] == 1e9, it cannot be reached from source, so skip it.
//            - For every outgoing edge (node -> nei) with weight wt:
//              `dist[nei] = min(dist[nei], dist[node] + wt);`
//    Step 5: Replace all remaining 1e9 values with -1 (unreachable nodes) and return dist.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> shortestPath(int N, int M, vector<vector<int>>& edges) {
        // Step 1: Build adjacency list: u -> {v, weight}
        vector<vector<pair<int, int>>> adj(N);
        for (auto& e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
        }

        // Step 2: Topological sort using DFS
        vector<int> vis(N, 0);
        stack<int> st;

        function<void(int)> dfs = [&](int node) {
            vis[node] = 1;
            for (auto [nei, wt] : adj[node]) {
                if (!vis[nei]) {
                    dfs(nei);
                }
            }
            st.push(node);
        };

        for (int i = 0; i < N; i++) {
            if (!vis[i]) {
                dfs(i);
            }
        }

        // Step 3: Initialize distances with infinity
        const int INF = 1e9;
        vector<int> dist(N, INF);
        dist[0] = 0; // Distance to source is 0

        // Step 4: Relax edges in topological order
        while (!st.empty()) {
            int node = st.top();
            st.pop();

            // If this node is not reachable from source, skip
            if (dist[node] == INF) continue;

            for (auto [nei, wt] : adj[node]) {
                if (dist[node] + wt < dist[nei]) {
                    dist[nei] = dist[node] + wt;
                }
            }
        }

        // Step 5: Mark unreachable vertices as -1
        for (int i = 0; i < N; i++) {
            if (dist[i] == INF) {
                dist[i] = -1;
            }
        }

        return dist;
    }
};

/*
Time Complexity: O(V + E)
- Building the adjacency list: O(E) where E = M.
- Finding Topological Sort using DFS: O(V + E).
- Relaxing edges: each vertex is popped once and each edge is examined once: O(V + E).
- Final pass to convert unreachable nodes: O(V).
- Overall Time Complexity: O(V + E) (Strictly Linear Time).

Space Complexity: O(V + E)
- Adjacency list: O(V + E).
- Visited array: O(V).
- Topological sort stack: O(V).
- Distance array: O(V).
- Overall Auxiliary Space: O(V + E).

Key Insights:
1. Why Processing in Topological Order Guarantees Correct Shortest Path:
   - For any path reaching vertex v from u, u MUST appear before v in the topological sort.
   - Therefore, by the time we process v, all possible paths leading into v have already 
     been fully relaxed and considered.
2. Faster than Dijkstra:
   - Dijkstra's uses a priority queue (O((V + E) log V)).
   - Topo Sort solves DAG shortest paths in linear O(V + E) without any priority queue overhead.
*/
