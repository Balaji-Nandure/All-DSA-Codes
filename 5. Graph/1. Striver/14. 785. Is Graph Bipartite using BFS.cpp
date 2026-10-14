// Problem: 785. Is Graph Bipartite? (using BFS)
// Link (LeetCode): https://leetcode.com/problems/is-graph-bipartite/
// Link (GFG): https://www.geeksforgeeks.org/problems/bipartite-graph/1
// Difficulty: Medium
// Topic: Graph, BFS, 2-Coloring, Bipartite Graph

/*
Problem Statement:
There is an undirected graph with n nodes, where each node is numbered between 0 and n - 1. 
You are given a 2D array graph, where graph[u] is an array of nodes that node u is adjacent to.

A graph is bipartite if the nodes can be partitioned into two independent sets A and B 
such that every edge in the graph connects a node in set A and a node in set B.

Equivalently: A graph is bipartite if and only if it can be colored using 2 colors 
such that no two adjacent nodes have the same color.

Return true if and only if it is bipartite.

Example 1:
Input: graph = [[1,2,3],[0,2],[0,1,3],[0,2]]
Output: false
Explanation: There is an odd cycle: 0 -> 1 -> 2 -> 0 (length 3).
It is impossible to color the graph with 2 colors without two adjacent vertices sharing the same color.

Example 2:
Input: graph = [[1,3],[0,2],[1,3],[0,2]]
Output: true
Explanation: We can partition the nodes into two sets: {0, 2} and {1, 3}.
Color nodes 0 and 2 with color 0, and nodes 1 and 3 with color 1.

Constraints:
- graph.length == n
- 1 <= n <= 100
- 0 <= graph[u].length < n
- 0 <= graph[u][i] <= n - 1
- graph[u] does not contain u (no self-loops).
- All the values of graph[u] are unique.
- The graph is undirected (if v is in graph[u], then u is in graph[v]).
*/

// Approach: BFS with 2-Coloring
// 1. Maintain a color array initialized to -1 for all nodes (indicating uncolored).
// 2. The graph may be disconnected, so loop through all vertices 0 to n-1.
// 3. For any uncolored vertex, start BFS:
//    - Color the starting node with color 0 and push it to the queue.
// 4. While the queue is not empty:
//    - Pop the current node.
//    - For each adjacent neighbor:
//      a. If uncolored (color == -1):
//         - Assign opposite color: 1 - color[current].
//         - Push neighbor to queue.
//      b. If already colored and has the SAME color as current node:
//         - Adjacent nodes share the same color -> NOT bipartite -> return false.
// 5. If all nodes and components are processed without conflict, the graph is bipartite -> return true.

#include <bits/stdc++.h>
using namespace std;

// Approach 1: BFS with Modular Helper Function
class Solution {
private:
    bool checkBipartiteBFS(int start, vector<vector<int>>& graph, vector<int>& color) {
        queue<int> q;
        q.push(start);
        color[start] = 0; // Assign initial color 0

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int neighbor : graph[node]) {
                // If neighbor is not yet colored, give it the opposite color
                if (color[neighbor] == -1) {
                    color[neighbor] = 1 - color[node];
                    q.push(neighbor);
                }
                // If neighbor already has the same color, graph is not bipartite
                else if (color[neighbor] == color[node]) {
                    return false;
                }
            }
        }
        return true;
    }

public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        // -1: uncolored, 0: color A, 1: color B
        vector<int> color(n, -1);

        // Check each connected component
        for (int i = 0; i < n; i++) {
            if (color[i] == -1) {
                if (!checkBipartiteBFS(i, graph, color)) {
                    return false;
                }
            }
        }
        return true;
    }
};

/*
Time Complexity: O(V + 2E)
- In BFS, every vertex is enqueued and processed once: O(V).
- For every vertex, we iterate over all its adjacent edges: total edge traversals = 2E (for undirected graph).
- Overall Time Complexity: O(V + E)

Space Complexity: O(V)
- color array of size V: O(V)
- BFS queue stores at most V nodes: O(V)
- Total Auxiliary Space: O(V)

Key Insights:
1. Fundamental Bipartite Theorem:
   - Any graph with NO cycles is ALWAYS bipartite (e.g. Trees).
   - Any graph with EVEN-length cycles is ALWAYS bipartite.
   - Any graph with at least one ODD-length cycle can NEVER be bipartite.
2. 2-Coloring via BFS:
   - BFS visits nodes layer by layer (by distance from start).
   - If an edge exists between two nodes in the same layer or having the same color,
     an odd-length cycle exists, breaking the bipartite property.
3. Disconnected Graphs:
   - Always run the check across an outer loop (0 to n-1) to handle graphs with multiple isolated components.
*/
