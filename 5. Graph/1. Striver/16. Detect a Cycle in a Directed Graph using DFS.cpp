// Problem: Detect a Cycle in a Directed Graph using DFS
// Link: https://www.geeksforgeeks.org/problems/detect-cycle-in-a-directed-graph/1
// Difficulty: Medium
// Topic: DFS, Graph, Directed Graph, Cycle Detection, Backtracking

/*
Problem Statement:
Given a Directed Graph with V vertices (numbered from 0 to V-1) and E edges, 
check whether it contains any cycle or not.

Example 1:
Input: V = 4, E = 4
Edges: 0 -> 1, 1 -> 2, 2 -> 3, 3 -> 1
Output: 1
Explanation: 1 -> 2 -> 3 -> 1 is a cycle.

Example 2:
Input: V = 4, E = 4
Edges: 0 -> 1, 0 -> 2, 1 -> 3, 2 -> 3
Output: 0
Explanation: No cycle exists. Even though node 3 is reached from both 1 and 2 (cross path), 
there is no path back to an ancestor.

Constraints:
- 1 <= V, E <= 10^5
*/

// Approach: DFS with Path Visited / Recursion Stack Tracking -> 2nd method is the best one.
// 1. Why Undirected Graph logic doesn't work:
//    - In an undirected graph, checking (visited[neighbor] && neighbor != parent) is sufficient.
//    - In a directed graph, a node may be visited through another branch without forming a cycle.
//    - A cycle exists if and only if we encounter a node that is currently in the SAME recursion path (Back Edge).
// 2. We maintain two arrays (or two states):
//    - vis[node]: true if node was visited in any traversal.
//    - pathVis[node]: true if node is on the current DFS recursion stack.
// 3. For each unvisited node:
//    - Mark vis[node] = true and pathVis[node] = true.
//    - For each directed neighbor:
//      a. If unvisited: recursively call DFS. If it returns true, a cycle exists.
//      b. If visited AND pathVis[neighbor] == true: cycle detected (back edge)!
//    - On backtracking: unmark pathVis[node] = false.
// 4. Handle disconnected components by iterating through all vertices 0 to V-1.

#include <bits/stdc++.h>
using namespace std;

// // Approach 1: Using Two Arrays (vis and pathVis) - Standard Striver Approach
// class Solution {
// private:
//     bool dfsCheck(int node, vector<vector<int>>& adj, vector<bool>& vis, vector<bool>& pathVis) {
//         vis[node] = true;
//         pathVis[node] = true;

//         // Traverse all adjacent nodes in directed edges (node -> neighbor)
//         for (auto neighbor : adj[node]) {
//             // When neighbor is not yet visited
//             if (!vis[neighbor]) {
//                 if (dfsCheck(neighbor, adj, vis, pathVis)) {
//                     return true;
//                 }
//             }
//             // If neighbor is previously visited on the SAME path, cycle exists
//             else if (pathVis[neighbor]) {
//                 return true;
//             }
//         }

//         // Backtrack: Remove node from current recursion path
//         pathVis[node] = false;
//         return false;
//     }

// public:
//     // Function to detect cycle in a directed graph
//     bool isCyclic(int V, vector<vector<int>>& adj) {
//         vector<bool> vis(V, false);
//         vector<bool> pathVis(V, false);

//         // Check for cycle in each component
//         for (int i = 0; i < V; i++) {
//             if (!vis[i]) {
//                 if (dfsCheck(i, adj, vis, pathVis)) {
//                     return true;
//                 }
//             }
//         }
//         return false;
//     }
// };

// Approach 2: Optimized using Single Array (3 States / Tri-color DFS)
// State 0: Unvisited
// State 1: Visiting (currently in recursion stack / pathVis)
// State 2: Visited (fully processed, no cycle found through this path)
class SolutionOptimized {
private:
    bool dfsCheck(int node, vector<vector<int>>& adj, vector<int>& state) {
        state[node] = 1; // Mark as currently visiting (on call stack)

        for (auto neighbor : adj[node]) {
            if (state[neighbor] == 0) {
                if (dfsCheck(neighbor, adj, state)) {
                    return true;
                }
            }
            // Re-visiting a node currently on the call stack means back edge -> cycle!
            else if (state[neighbor] == 1) {
                return true;
            }
        }

        state[node] = 2; // Mark as fully processed (safe)
        return false;
    }

public:
    bool isCyclic(int V, vector<vector<int>>& adj) {
        vector<int> state(V, 0); // 0: unvisited, 1: visiting, 2: visited

        for (int i = 0; i < V; i++) {
            if (state[i] == 0) {
                if (dfsCheck(i, adj, state)) {
                    return true;
                }
            }
        }
        return false;
    }
};

/*
Time Complexity: O(V + E)
- In a directed graph, every vertex is visited at most once: O(V).
- Every directed edge is traversed at most once: O(E).
- Total Time Complexity: O(V + E)

Space Complexity: O(V)
- vis array: O(V)
- pathVis array: O(V)
- Recursion call stack: O(V) in worst case (e.g. linear chain 0 -> 1 -> 2 -> ... -> V-1).
- Total Auxiliary Space: O(V)

Key Insights:
1. Difference between Undirected vs Directed Cycle Detection:
   - Undirected: Any edge to an already-visited non-parent node indicates a cycle.
   - Directed: Cross edges to already-visited nodes DO NOT indicate a cycle unless that node 
     is part of the ACTIVE recursion path (ancestor in the current path).
2. Backtracking is Crucial:
   - Resetting pathVis[node] = false when DFS returns allows that node to be part of other paths 
     without false positives.
3. State Optimization:
   - Using 3 states (0 = unvisited, 1 = in stack, 2 = visited) combines vis and pathVis into a 
     single integer vector, saving memory.
*/
