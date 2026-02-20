// Problem: Detect a Cycle in an Undirected Graph using DFS
// Link: https://www.geeksforgeeks.org/problems/detect-cycle-in-an-undirected-graph/1
// Difficulty: Medium
// Topic: DFS, Graph, Cycle Detection

/*
Problem Statement:
Given an undirected graph with V vertices and E edges, check whether it contains any cycle or not.

Example 1:
Input: V = 5, E = 5
adj = {{1}, {0, 2, 4}, {1, 3}, {2, 4}, {1, 3}}
Output: 1
Explanation: 1->2->3->4->1 is a cycle.

Example 2:
Input: V = 4, E = 2
adj = {{}, {2}, {1, 3}, {2}}
Output: 0
Explanation: No cycle in the graph.

Constraints:
- 1 ≤ V, E ≤ 10^5
*/

// Approach: DFS with Parent Tracking
// 1. For each unvisited node, start DFS
// 2. Track parent of each node during traversal
// 3. If we visit a node that is already visited and is not the parent of current node,
//    then there is a cycle
// 4. Handle disconnected components by iterating through all nodes

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    bool detectCycleDFS(int node, int parent, vector<vector<int>>& adj, vector<bool>& visited) {
        visited[node] = true;
        
        // Traverse all adjacent nodes
        for (auto neighbor : adj[node]) {
            if (!visited[neighbor]) {
                // Recursively check for cycle in unvisited neighbor
                if (detectCycleDFS(neighbor, node, adj, visited)) {
                    return true;
                }
            }
            // If neighbor is visited and is not the parent, cycle exists
            else if (neighbor != parent) {
                return true;
            }
        }
        return false;
    }
    
public:
    // Function to detect cycle in an undirected graph
    bool isCycle(int V, vector<vector<int>>& edges) {
        // Build adjacency list from edges
        vector<vector<int>> adj(V);
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        vector<bool> visited(V, false);
        
        // Check for cycle in each connected component
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                if (detectCycleDFS(i, -1, adj, visited)) {
                    return true;
                }
            }
        }
        return false;
    }
};

/*
Time Complexity: O(V + E)
- We visit each vertex once and traverse all edges

Space Complexity: O(V + E)
- Adjacency list: O(V + E)
- Visited array: O(V)
- Recursion stack: O(V) in worst case (for a linear graph)

Key Insight:
- In DFS, if we reach a visited node that is NOT the parent of current node,
  it means we've found another path to that node, indicating a cycle.
- We need to track parent because in undirected graph, going back to parent
  doesn't count as a cycle.
- DFS uses recursion stack instead of explicit queue like BFS.
*/

