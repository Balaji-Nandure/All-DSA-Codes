// Problem: 785. Is Graph Bipartite? (using DFS)
// Link (LeetCode): https://leetcode.com/problems/is-graph-bipartite/
// Link (GFG): https://www.geeksforgeeks.org/problems/bipartite-graph/1
// Difficulty: Medium
// Topic: Graph, DFS, 2-Coloring, Bipartite Graph, Recursion

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

// Approach: DFS with 2-Coloring
// 1. Maintain a color array initialized to -1 for all nodes (indicating uncolored).
// 2. Iterate through all vertices 0 to n-1 to handle disconnected components.
// 3. For any uncolored vertex, call DFS starting with color 0.
// 4. Inside DFS(node, col):
//    - Assign color[node] = col.
//    - For each adjacent neighbor of node:
//      a. If uncolored (color[neighbor] == -1):
//         - Recursively call DFS with opposite color (1 - col).
//         - If any recursive call returns false, immediately return false.
//      b. If already colored and color[neighbor] == col:
//         - Two adjacent nodes have the same color -> odd cycle detected -> return false.
// 5. If all neighbors can be colored without conflict, return true.

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    bool checkBipartiteDFS(int node, int col, vector<vector<int>>& graph, vector<int>& color) {
        color[node] = col;

        // Traverse all adjacent nodes
        for (int neighbor : graph[node]) {
            // If neighbor has not been colored yet
            if (color[neighbor] == -1) {
                // Recursively color neighbor with opposite color (1 - col)
                if (!checkBipartiteDFS(neighbor, 1 - col, graph, color)) {
                    return false;
                }
            }
            // If neighbor is already colored with the same color, not bipartite
            else if (color[neighbor] == col) {
                return false;
            }
        }
        return true;
    }

public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        // -1: uncolored, 0: color A, 1: color B
        vector<int> color(n, -1);

        // Check for each connected component
        for (int i = 0; i < n; i++) {
            if (color[i] == -1) {
                if (!checkBipartiteDFS(i, 0, graph, color)) {
                    return false;
                }
            }
        }
        return true;
    }
};

/*
Time Complexity: O(V + 2E)
- Each vertex is visited once and colored: O(V).
- For every vertex, we traverse all its adjacent edges: total edge traversals = 2E (for undirected graph).
- Overall Time Complexity: O(V + E)

Space Complexity: O(V)
- color array of size V: O(V)
- Recursion call stack: O(V) in worst case (e.g. linear graph).
- Total Auxiliary Space: O(V)

Key Insights:
1. DFS vs BFS for Bipartite:
   - Both BFS and DFS run in O(V + E) time and O(V) space.
   - DFS uses the recursion call stack, while BFS uses an explicit std::queue.
2. Odd-Cycle Detection:
   - When DFS encounters a back-edge to an already colored node with the SAME color,
     it proves the existence of an odd-length cycle.
   - Any graph with even-length cycles only or no cycles (trees, DAGs) is always bipartite.
3. Multiple Components:
   - An outer loop from 0 to n-1 is necessary because disconnected components might independently be 
     bipartite or non-bipartite.
*/
