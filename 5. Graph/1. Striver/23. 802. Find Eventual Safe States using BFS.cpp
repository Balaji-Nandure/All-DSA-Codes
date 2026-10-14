// Problem: 802. Find Eventual Safe States (using BFS / Topological Sort / Kahn's Algorithm)
// Link (LeetCode): https://leetcode.com/problems/find-eventual-safe-states/
// Link (GFG): https://www.geeksforgeeks.org/problems/eventual-safe-states/1
// Difficulty: Medium
// Topic: Graph, BFS, Topological Sort, Kahn's Algorithm, Directed Graph, Indegree

/*
Problem Statement:
There is a directed graph of n nodes with each node labeled from 0 to n - 1. 
The graph is represented by a 0-indexed 2D integer array graph where graph[i] is an integer array 
of nodes adjacent to node i, meaning there is an edge from node i to each node in graph[i].

A node is a terminal node if there are no outgoing edges. 
A node is a safe node if every possible path starting from that node leads to a terminal node (or another safe node).

Return an array containing all the safe nodes of the graph. The answer should be sorted in ascending order.

Example 1:
Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
Output: [2,4,5,6]
Explanation:
- Nodes 5 and 6 are terminal nodes since they have no outgoing edges.
- Paths from node 2: 2 -> 5 (terminal) => SAFE.
- Paths from node 4: 4 -> 5 (terminal) => SAFE.
- Nodes 0, 1, 3 are in a cycle: 0 -> 1 -> 2 -> 3 -> 0 (leads back to cycle) => UNSAFE.

Example 2:
Input: graph = [[1,2,3,4],[1,2],[3,4],[0,4],[]]
Output: [4]
Explanation: Only node 4 is a terminal node, and every other node can loop into the cycle formed by 0, 1, 2, 3.

Constraints:
- n == graph.length
- 1 <= n <= 10^4
- 0 <= graph[i].length <= n
- 0 <= graph[i][j] <= n - 1
- graph[i] is sorted in strictly increasing order.
- The graph may contain self-loops.
- The number of edges in the graph will be in the range [1, 4 * 10^4].
*/

// Approach: Kahn's Algorithm / BFS via Graph Reversal
// 1. Core Intuition:
//    - Terminal nodes in the original graph have outdegree == 0.
//    - A node is SAFE if all paths originating from it lead to terminal nodes.
//    - Kahn's algorithm works from sources (nodes with indegree 0) forward to resolve dependencies.
//    - But safe nodes are defined from sinks (nodes with outdegree 0) backward!
// 2. The Graph Reversal Trick:
//    - If we reverse all edges in the graph (i -> it becomes it -> i in adjRev):
//      * Terminal nodes (outdegree 0) become source nodes with indegree == 0!
//      * Now we can apply standard Kahn's Algorithm starting from these terminal nodes.
// 3. Algorithm Steps:
//    Step 1: Reverse all directed edges: for every i -> it in graph, add it -> i in adjRev.
//    Step 2: Calculate in-degree for all vertices in adjRev:
//            `for (int i = 0; i < V; i++) for (auto it : adjRev[i]) indegree[it]++;`
//    Step 3: Push all nodes with indegree == 0 (original terminal nodes) into queue.
//    Step 4: Standard Kahn's BFS traversal:
//            - Pop `node`, append it to `safeNodes`.
//            - For each adjacent neighbor `it` in `adjRev[node]`:
//              - Decrement `indegree[it]--`.
//              - If `indegree[it] == 0`, all its original outgoing paths have safely resolved! Push `it` to queue.
//    Step 5: Nodes trapped in or leading to cycles will never reach indegree 0.
//    Step 6: Sort `safeNodes` in ascending order and return.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int V = graph.size();
        vector<vector<int>> adjRev(V);

        // Step 1: Reverse all the edges (i -> it becomes it -> i)
        for (int i = 0; i < V; i++) {
            for (auto it : graph[i]) {
                adjRev[it].push_back(i);
            }
        }

        // Step 2: Calculate in-degree for all vertices in adjRev
        vector<int> indegree(V, 0);
        for (int i = 0; i < V; i++) {
            for (auto it : adjRev[i]) {
                indegree[it]++;
            }
        }

        // Step 3: Push all terminal nodes (indegree == 0 in adjRev) into queue
        queue<int> q;
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        // Step 4: Standard Kahn's BFS
        vector<int> safeNodes;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            safeNodes.push_back(node);

            // Traverse all reversed edges (pointing to parents in original graph)
            for (auto it : adjRev[node]) {
                indegree[it]--;

                // If all outgoing edges of 'it' in original graph are resolved
                if (indegree[it] == 0) {
                    q.push(it);
                }
            }
        }

        // Step 5: Sort result in ascending order as required
        sort(safeNodes.begin(), safeNodes.end());
        return safeNodes;
    }
};

/*
Time Complexity: O(V + E + V log V)
- Reversing edges and computing in-degrees: O(V + E)
- Initializing the queue: O(V)
- BFS traversal visiting safe nodes and edges: O(V + E)
- Sorting safeNodes of size at most V: O(V log V)
- Overall Time Complexity: O(V + E + V log V)

Space Complexity: O(V + E)
- adjRev (reversed adjacency list): O(V + E)
- indegree array: O(V)
- BFS queue: O(V)
- Output vector safeNodes: O(V)
- Overall Auxiliary Space: O(V + E)

Key Insights:
1. Why Graph Reversal is Genius here:
   - Kahn's algorithm works naturally from indegree 0 (sources).
   - In Eventual Safe States, we need to work from outdegree 0 (sinks).
   - Reversing edges converts sinks into sources, allowing the exact same Kahn's algorithm 
     to work without modification!
2. Automatic Cycle Elimination:
   - Nodes in a cycle or pointing into a cycle will always retain an unresolved dependency 
     (indegree > 0), so they are never added to the queue.
*/
