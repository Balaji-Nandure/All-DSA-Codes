/**
 * Problem: Detect Cycle in an Undirected Graph using BFS and DFS
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In a Directed Graph, edges have single orientation and we checked for back-edges via recursion stack.
 * - In an Undirected Graph, an edge `u - v` naturally reflects back as `v - u`.
 * - Returning to the immediate parent is NOT a cycle; a cycle is confirmed IF AND ONLY IF an already-visited
 *   neighbor is NOT the immediate parent from which we arrived.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Parent Tracking DFS & BFS:
 *   - Method 1: DFS with Parent Parameter:
 *     - Traverse from `u` with predecessor `parent`.
 *     - For each neighbor `v`:
 *       - If `!visited[v]`: Recurse with `v` and parent `u`.
 *       - If `visited[v] == true && v != parent`: An independent alternate loop exists -> CYCLE!
 *   - Method 2: BFS with `{node, parent}` Queue:
 *     - Enqueue pair `{source, -1}`.
 *     - When expanding `u`: if neighbor `v` is visited and `v != parent`, cycle exists.
 * 
 * TIME COMPLEXITY:
 * - O(V + E) for both BFS and DFS.
 * 
 * SPACE COMPLEXITY:
 * - O(V) for visited array and BFS queue / DFS recursion stack.
 */

#include <iostream>
#include <vector>
#include <queue>

// Method 1: DFS with parent tracking
bool dfsCycle(int u, int parent, const std::vector<std::vector<int>>& adj, std::vector<bool>& visited) {
    visited[u] = true;

    for (int v : adj[u]) {
        if (!visited[v]) {
            if (dfsCycle(v, u, adj, visited)) return true;
        } else if (v != parent) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // An already visited neighbor that is NOT our direct predecessor confirms an alternate cyclic loop!
            return true;
        }
    }

    return false;
}

// Method 2: BFS with parent tracking
bool bfsCycle(int start, const std::vector<std::vector<int>>& adj, std::vector<bool>& visited) {
    std::queue<std::pair<int, int>> q; // {node, parent}
    visited[start] = true;
    q.push({start, -1});

    while (!q.empty()) {
        auto [u, parent] = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push({v, u});
            } else if (v != parent) {
                return true;
            }
        }
    }

    return false;
}

bool isCycle(int V, const std::vector<std::vector<int>>& adj) {
    std::vector<bool> visitedDFS(V, false);
    for (int i = 0; i < V; i++) {
        if (!visitedDFS[i]) {
            if (dfsCycle(i, -1, adj, visitedDFS)) return true;
        }
    }
    return false;
}

int main() {
    int V = 5;
    std::vector<std::vector<int>> adj(V);
    // Cycle: 0-1-2-0
    adj[0] = {1, 2};
    adj[1] = {0, 2};
    adj[2] = {0, 1, 3};
    adj[3] = {2, 4};
    adj[4] = {3};

    std::cout << "Cycle in undirected graph: " << (isCycle(V, adj) ? "Yes" : "No") << "\n"; // Yes

    return 0;
}
