/**
 * Problem: Detect Cycle in a Directed Graph using BFS and DFS
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In undirected graphs, traversing back to the immediate parent does not mean a cycle exists.
 * - In a DIRECTED graph, an edge `u -> v` is a cycle IF AND ONLY IF `v` is an ancestor currently active
 *   in the current recursion path (a BACK-EDGE).
 * - Visiting an already visited node that has finished its recursion (cross-edge or forward-edge) does NOT constitute a cycle.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Method 1: DFS with Recursion Stack / Path-Visited:
 *   - Maintain two boolean arrays:
 *     - `visited[u]`: Tracks if vertex has ever been visited globally.
 *     - `inStack[u]`: Tracks if vertex is currently active on the CURRENT recursion stack path.
 *   - When traversing edge `u -> v`:
 *     - If `!visited[v]`: Recurse on `v`.
 *     - If `inStack[v] == true`: A BACK EDGE is detected! This directly completes a directed cycle -> return true!
 *   - Backtrack: unmark `inStack[u] = false` when exiting recursive call.
 * - Method 2: BFS Kahn's Algorithm (Topological Sort):
 *   - In a Directed Acyclic Graph (DAG), Kahn's algorithm processes all V vertices.
 *   - If the count of processed vertices `< V`, vertices caught in a cycle never reach in-degree 0 -> CYCLE exists!
 * 
 * TIME COMPLEXITY:
 * - O(V + E) for both BFS and DFS.
 * 
 * SPACE COMPLEXITY:
 * - O(V) for visited and inStack arrays.
 */

#include <iostream>
#include <vector>
#include <queue>

// Method 1: DFS with inStack tracking
bool isCyclicDFS(int u, const std::vector<std::vector<int>>& adj, 
                std::vector<bool>& visited, std::vector<bool>& inStack) {
    visited[u] = true;
    inStack[u] = true;

    for (int v : adj[u]) {
        if (!visited[v]) {
            if (isCyclicDFS(v, adj, visited, inStack)) return true;
        } else if (inStack[v]) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Back-edge detected: neighbor v is currently active on the ancestral recursion stack!
            return true;
        }
    }

    inStack[u] = false; // Backtrack
    return false;
}

bool hasCycleDFS(int V, const std::vector<std::vector<int>>& adj) {
    std::vector<bool> visited(V, false);
    std::vector<bool> inStack(V, false);

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (isCyclicDFS(i, adj, visited, inStack)) return true;
        }
    }
    return false;
}

// Method 2: BFS Kahn's Algorithm (Topological Sort reduction)
bool hasCycleBFS(int V, const std::vector<std::vector<int>>& adj) {
    std::vector<int> inDegree(V, 0);
    for (int u = 0; u < V; u++) {
        for (int v : adj[u]) {
            inDegree[v]++;
        }
    }

    std::queue<int> q;
    for (int i = 0; i < V; i++) {
        if (inDegree[i] == 0) q.push(i);
    }

    int count = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        count++;

        for (int v : adj[u]) {
            inDegree[v]--;
            if (inDegree[v] == 0) q.push(v);
        }
    }

    // If topological sort does not include all vertices, a cycle exists
    return count != V;
}

int main() {
    int V = 4;
    std::vector<std::vector<int>> adj(V);
    // Cycle: 0 -> 1 -> 2 -> 3 -> 1
    adj[0] = {1};
    adj[1] = {2};
    adj[2] = {3};
    adj[3] = {1};

    std::cout << "Cycle detected via DFS: " << (hasCycleDFS(V, adj) ? "Yes" : "No") << "\n"; // Yes
    std::cout << "Cycle detected via BFS: " << (hasCycleBFS(V, adj) ? "Yes" : "No") << "\n"; // Yes

    return 0;
}
