/**
 * Problem: Depth First Search (DFS) Traversal of Graph
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - BFS explored breadth-first radially outward level-by-level using a FIFO queue.
 * - DFS plunges as deep as possible along each branch before backtracking, using the execution call stack
 *   alongside the visited set.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Recursive Backtracking DFS:
 *   - Mark current vertex `u` as visited: `visited[u] = true`.
 *   - Append `u` to traversal result.
 *   - Iterate through every adjacent vertex `v` of `u`:
 *     - If `!visited[v]`, recursively plunge down vertex `v`.
 *   - Automatically explores entire connected components before backtracking to alternative unvisited branches.
 * 
 * TIME COMPLEXITY:
 * - O(V + E): Visits every reachable vertex and explores every incident edge once.
 * 
 * SPACE COMPLEXITY:
 * - O(V) auxiliary recursion stack depth and visited array.
 */

#include <iostream>
#include <vector>

void dfsUtil(int u, const std::vector<std::vector<int>>& adj, std::vector<bool>& visited, std::vector<int>& dfs) {
    visited[u] = true;
    dfs.push_back(u);

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Deeply traverse each unvisited branch recursively before backtracking to siblings.
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfsUtil(v, adj, visited, dfs);
        }
    }
}

std::vector<int> dfsOfGraph(int V, const std::vector<std::vector<int>>& adj) {
    std::vector<int> dfs;
    std::vector<bool> visited(V, false);

    // Start DFS from vertex 0
    dfsUtil(0, adj, visited, dfs);

    return dfs;
}

int main() {
    int V = 5;
    std::vector<std::vector<int>> adj(V);
    adj[0] = {1, 2, 4};
    adj[1] = {0};
    adj[2] = {0};
    adj[3] = {4};
    adj[4] = {0, 3};

    std::vector<int> res = dfsOfGraph(V, adj);
    std::cout << "DFS Traversal: ";
    for (int x : res) std::cout << x << " ";
    std::cout << "\n"; // 0 1 2 4 3

    return 0;
}
