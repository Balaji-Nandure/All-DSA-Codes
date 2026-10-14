// Problem: Topological Sort (using DFS)
// Link: https://www.geeksforgeeks.org/problems/topological-sort/1
// Difficulty: Medium
// Topic: Graph, DFS, Topological Sort, DAG, Stack

/*
Problem Statement:
Given a Directed Acyclic Graph (DAG) with V vertices and E edges, 
find any valid Topological Sorting of that graph.

Topological sorting for a Directed Acyclic Graph (DAG) is a linear ordering of vertices 
such that for every directed edge u -> v, vertex u comes before vertex v in the ordering.

Note:
- Topological sort is ONLY defined for Directed Acyclic Graphs (DAGs).
- If a graph contains a cycle, no topological ordering exists.
- A graph can have multiple valid topological sort orderings.

Example 1:
Input: V = 6, E = 6
Edges: 5 -> 0, 5 -> 2, 4 -> 0, 4 -> 1, 2 -> 3, 3 -> 1
Output: 5 4 2 3 1 0 (or 4 5 2 3 1 0)
Explanation:
- 5 appears before 0 and 2.
- 4 appears before 0 and 1.
- 2 appears before 3.
- 3 appears before 1.
Every directed edge u -> v has u appearing before v.

Example 2:
Input: V = 4, E = 3
Edges: 1 -> 0, 2 -> 0, 3 -> 0
Output: 3 2 1 0 (any ordering where 1, 2, 3 appear before 0)

Constraints:
- 2 <= V <= 10^4
- 1 <= E <= (V * (V - 1)) / 2
*/

// Approach: DFS with Stack (Post-Order Traversal)
// 1. Intuition:
//    - For any directed edge u -> v, u must appear before v in the topological order.
//    - When we run DFS from u, we first recursively visit all nodes reachable from u (including v).
//    - Therefore, v and all its descendants complete their DFS calls BEFORE u finishes.
// 2. The Stack Mechanism:
//    - If we push a node to a stack only AFTER all its neighbors/children are completely visited,
//      then v will be pushed to the stack BEFORE u.
//    - When we empty the stack (LIFO - Last In First Out), u will be popped BEFORE v!
//    - This naturally guarantees that every dependency is satisfied.
// 3. Handling Disconnected Components:
//    - Loop through all vertices 0 to V-1. If a vertex is not yet visited, trigger DFS from it.
// 4. Pop all elements from the stack into the answer vector to produce the final topological order.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void dfs(int node, vector<vector<int>>& adj,
             vector<int>& vis, stack<int>& st) {
        vis[node] = 1;

        // Traverse all directed neighbors
        for (int nei : adj[node]) {
            if (!vis[nei])
                dfs(nei, adj, vis, st);
        }

        // Push current node to stack after all its dependencies/neighbors are visited
        st.push(node);
    }

    // Function to return list containing vertices in Topological order
    vector<int> topoSort(int V, vector<vector<int>>& adj) {
        vector<int> vis(V, 0);
        stack<int> st;

        // Run DFS for all components
        for (int i = 0; i < V; i++) {
            if (!vis[i])
                dfs(i, adj, vis, st);
        }

        // Pop elements from stack to get topological order
        vector<int> ans;
        while (!st.empty()) {
            ans.push_back(st.top());
            st.pop();
        }

        return ans;
    }
};

/*
Time Complexity: O(V + E)
- In DFS, each vertex is visited once: O(V).
- Each directed edge is traversed once: O(E).
- Popping V elements from the stack: O(V).
- Overall Time Complexity: O(V + E)

Space Complexity: O(V)
- Visited array: O(V)
- Stack: O(V) to store all vertices
- Recursion call stack: O(V) in the worst case (linear DAG)
- Overall Auxiliary Space: O(V)

Key Insights:
1. Why DAG only?
   - If there is a cycle (e.g. u -> v -> w -> u), u must be before v, v before w, and w before u,
     which is mathematically impossible in a linear order.
2. Post-Order Traversal + Stack:
   - Pushing on backtrack guarantees that any vertex v reachable from u enters the stack first.
   - Reversing the order (via stack) ensures u appears before v in the final output.
3. Prerequisite for Advanced Graph Algorithms:
   - Topological sorting is the backbone for Shortest Path in DAGs, Course Schedule, Alien Dictionary,
     and Kahn's Algorithm.
*/
