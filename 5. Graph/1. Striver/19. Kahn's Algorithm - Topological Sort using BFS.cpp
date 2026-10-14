// Problem: Kahn's Algorithm (Topological Sort using BFS)
// Link: https://www.geeksforgeeks.org/problems/topological-sort/1
// Difficulty: Medium
// Topic: Graph, BFS, Topological Sort, DAG, Kahn's Algorithm, Indegree

/*
Problem Statement:
Given a Directed Acyclic Graph (DAG) with V vertices and E edges, 
find any valid Topological Sorting using Kahn's Algorithm (BFS).

Topological sort is a linear ordering of vertices such that for every directed edge u -> v, 
vertex u appears before vertex v in the ordering.

Example 1:
Input: V = 6, E = 6
Edges: 5 -> 0, 5 -> 2, 4 -> 0, 4 -> 1, 2 -> 3, 3 -> 1
Output: 4 5 0 2 3 1 (or 5 4 2 3 1 0)
Explanation:
- Both 4 and 5 have indegree 0 (no prerequisites), so they appear first.
- Every directed edge u -> v has u appearing before v.

Example 2:
Input: V = 4, E = 3
Edges: 1 -> 0, 2 -> 0, 3 -> 0
Output: 1 2 3 0 (any valid topological order)

Constraints:
- 2 <= V <= 10^4
- 1 <= E <= (V * (V - 1)) / 2
*/

// Approach: Kahn's Algorithm (BFS with In-degree)
// 1. Calculate the in-degree (number of incoming edges) for every vertex:
//    - For every node i, iterate through its adjacent neighbors `it` in adj[i] and increment `indegree[it]++`.
// 2. Insert all vertices with indegree == 0 into a queue (these have no incoming dependencies and can appear first).
// 3. While queue is not empty:
//    - Pop `node`, append it to `topo` result.
//    - For each adjacent neighbor `it` of `node`:
//      - Decrement `indegree[it]--` (removing the incoming edge from `node`).
//      - If `indegree[it] == 0`, all prerequisites for `it` are satisfied -> push `it` to queue.
// 4. Return `topo`.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to return list containing vertices in Topological order.
    vector<int> topoSort(int V, vector<vector<int>>& adj) {
        vector<int> indegree(V, 0);

        // Step 1: Calculate indegree for all vertices
        for (int i = 0; i < V; i++) {
            for (auto it : adj[i]) {
                indegree[it]++;
            }
        }

        // Step 2: Push all nodes with indegree == 0 to queue
        queue<int> q;
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        vector<int> topo;

        // Step 3: BFS traversal
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            topo.push_back(node);
            // node is in your topo sort
            // so please remove it from the indegree

            for (auto it : adj[node]) {
                indegree[it]--;
                if (indegree[it] == 0) {
                    q.push(it);
                }
            }
        }

        return topo;
    }
};

/*
Time Complexity: O(V + E)
- Calculating in-degrees: O(V + E) as we inspect every vertex and outgoing edge.
- Initializing queue: O(V).
- BFS traversal: each vertex is pushed/popped once: O(V).
- For each popped vertex, we iterate over all its outgoing edges: O(E).
- Overall Time Complexity: O(V + E)

Space Complexity: O(V)
- indegree array of size V: O(V)
- BFS queue stores at most V vertices: O(V)
- Overall Auxiliary Space: O(V)

Key Insights:
1. BFS vs DFS for Topological Sort:
   - DFS uses a Stack and post-order traversal (pushes when all children finish).
   - BFS (Kahn's) uses In-degree and a Queue (pushes when all parents finish).
2. Cycle Detection Intuition:
   - Nodes involved in a cycle will never have their indegree reduced to 0 because each node in 
     the cycle waits on another node in the cycle.
   - Hence, Kahn's algorithm naturally detects cycles: if topo.size() != V, a cycle exists.
*/
