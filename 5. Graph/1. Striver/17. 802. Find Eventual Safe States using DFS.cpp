// Problem: 802. Find Eventual Safe States (using DFS)
// Link (LeetCode): https://leetcode.com/problems/find-eventual-safe-states/
// Link (GFG): https://www.geeksforgeeks.org/problems/eventual-safe-states/1
// Difficulty: Medium
// Topic: DFS, Graph, Directed Graph, Cycle Detection

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

// Approach: 3-State DFS (Cycle Detection)
// 1. Intuition:
//    - Any node that is part of a cycle can never reach a terminal node (infinite loop).
//    - Any node that leads into a cycle is also unsafe.
//    - Therefore, a node is SAFE if and only if no path starting from it hits a cycle.
// 2. 3 States:
//    - State 0: Unvisited
//    - State 1: Visiting (currently in recursion call stack)
//    - State 2: Safe (all downstream paths lead to terminal nodes)
// 3. Algorithm:
//    - Mark state[node] = 1.
//    - For each neighbor `nei`:
//      - If state[nei] == 1, back edge found -> cycle detected -> return false.
//      - If state[nei] == 0 and dfs(nei) returns false -> cycle downstream -> return false.
//    - If all neighbors are safe, mark state[node] = 2 and return true.
//    - In main function, iterate i from 0 to n-1: run DFS if unvisited, and if state[i] == 2, collect i.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool dfs(int node, vector<vector<int>>& graph, vector<int>& state) {
        state[node] = 1;  // Visiting

        for (int nei : graph[node]) {
            if (state[nei] == 1) return false; // Cycle detected
            if (state[nei] == 0 && !dfs(nei, graph, state))
                return false;
        }

        state[node] = 2;  // Safe
        return true;
    }

    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> state(n, 0);
        vector<int> ans;

        for (int i = 0; i < n; i++) {
            if (state[i] == 0)
                dfs(i, graph, state);
            if (state[i] == 2)
                ans.push_back(i);
        }

        return ans;
    }
};

/*
Time Complexity: O(V + E)
- Each node is visited once during DFS: O(V).
- Each directed edge is traversed at most once: O(E).
- Final loop collects safe nodes in O(V).
- Overall Time Complexity: O(V + E)

Space Complexity: O(V)
- state vector of size V: O(V)
- Recursion call stack: O(V) in worst case (linear directed graph).
- Overall Auxiliary Space: O(V)

Key Insights:
1. Direct Boolean Safety:
   - Returning false immediately upon encountering a cycle (state == 1) or a path that leads to a 
     cycle allows fast propagation.
2. Natural Ascending Order:
   - By iterating 0 to n-1 in eventualSafeNodes, safe nodes are collected in ascending order 
     without requiring extra sorting.
*/
