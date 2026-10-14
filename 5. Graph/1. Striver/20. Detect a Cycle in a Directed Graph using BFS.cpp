// Problem: Detect a Cycle in a Directed Graph using BFS (Kahn's Algorithm)
// Link: https://www.geeksforgeeks.org/problems/detect-cycle-in-a-directed-graph/1
// Difficulty: Medium
// Topic: Graph, BFS, Kahn's Algorithm, Cycle Detection, Directed Graph, Indegree

/*
Problem Statement:
Given a Directed Graph with V vertices (numbered from 0 to V-1) and E edges, 
check whether it contains any cycle or not using BFS (Kahn's Algorithm).

Example 1:
Input: V = 4, E = 4
Edges: 0 -> 1, 1 -> 2, 2 -> 3, 3 -> 1
Output: 1 (True)
Explanation: 1 -> 2 -> 3 -> 1 is a cycle.

Example 2:
Input: V = 4, E = 4
Edges: 0 -> 1, 0 -> 2, 1 -> 3, 2 -> 3
Output: 0 (False)
Explanation: No cycle exists. It is a valid Directed Acyclic Graph (DAG).

Constraints:
- 1 <= V, E <= 10^5
*/

// Approach: Cycle Detection via Kahn's Algorithm (BFS)
// 1. Core Principle:
//    - Topological Sort is ONLY possible for Directed Acyclic Graphs (DAGs).
//    - If a graph has NO cycle, Kahn's algorithm will process ALL V vertices (count == V).
//    - If a graph contains a cycle:
//      * Nodes involved in a cycle will always have indegree >= 1 (each waiting for another in the cycle).
//      * Hence, they can NEVER reach indegree == 0 and are NEVER pushed into the queue.
//      * As a result, the total number of processed vertices will be strictly LESS than V (count < V).
// 2. Algorithm Steps:
//    Step 1: Calculate indegree for each vertex (using Striver's loop: `for(auto it : adj[i]) indegree[it]++`).
//    Step 2: Push all vertices with indegree == 0 into a BFS queue.
//    Step 3: Keep a counter `count = 0` (or topo vector size).
//    Step 4: While queue is not empty:
//            - Pop `node`, increment `count++`.
//            - For every neighbor `it` of `node`:
//              - Decrement `indegree[it]--`.
//              - If `indegree[it] == 0`, push `it` to queue.
//    Step 5: If `count == V`, no cycle exists -> return false.
//            If `count < V`, cycle exists -> return true.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to detect cycle in a directed graph using Kahn's Algorithm (BFS)
    bool isCyclic(int V, vector<vector<int>>& adj) {
        vector<int> indegree(V, 0);

        // Step 1: Calculate indegree for all vertices
        for (int i = 0; i < V; i++) {
            for (auto it : adj[i]) {
                indegree[it]++;
            }
        }

        // Step 2: Push all nodes with indegree == 0 into queue
        queue<int> q;
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        int count = 0;

        // Step 3: BFS traversal
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            count++; // Track number of vertices successfully processed

            for (auto it : adj[node]) {
                indegree[it]--;
                if (indegree[it] == 0) {
                    q.push(it);
                }
            }
        }

        // If count == V, a complete topological sort was generated -> DAG (No cycle)
        // If count < V, some vertices could not be processed due to dependencies in a cycle -> Cycle exists!
        return count != V;
    }
};

/*
Time Complexity: O(V + E)
- Calculating in-degrees: O(V + E).
- Initializing the queue: O(V).
- BFS traversal: each valid node is pushed and popped at most once: O(V).
- In total, each edge is traversed once: O(E).
- Overall Time Complexity: O(V + E)

Space Complexity: O(V)
- indegree array: O(V)
- BFS queue: O(V) in worst case
- Overall Auxiliary Space: O(V)

Key Insights:
1. DFS vs BFS for Directed Cycle Detection:
   - DFS checks if a node encounters an ancestor currently active on the recursion stack (`pathVis` or `state == 1`).
   - BFS (Kahn's) relies on the property that nodes in a cycle never drop to in-degree 0.
2. Space Efficiency:
   - We do not even need to store the `topo` array. A simple integer `count` is sufficient to 
     determine if all V vertices were reachable.
3. Intuition Summary:
   - DAG: count == V (return false).
   - Cyclic: count < V (return true).
*/
