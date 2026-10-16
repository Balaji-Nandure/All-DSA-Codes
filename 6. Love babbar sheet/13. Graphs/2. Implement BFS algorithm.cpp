/**
 * Problem: Breadth First Search (BFS) Traversal of Graph
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Tree BFS (Level Order) never encountered cycles; a node had a single parent and could never be revisited.
 * - In Graphs, cycles and multiple alternative paths exist between vertices!
 * - An explicit `visited[]` boolean array is MANDATORY to prevent infinite cyclic loops.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Queue-Based Level-by-Level Expansion:
 *   - Use a FIFO queue `std::queue<int>`.
 *   - Mark starting vertex as visited and push to queue.
 *   - While queue is not empty:
 *     - Pop front vertex `u`, record in BFS traversal.
 *     - For each unvisited neighbor `v` of `u`:
 *       - Mark `visited[v] = true` IMMEDIATELY upon enqueueing!
 *       - Push `v` to queue.
 *     - Why mark visited upon push rather than upon pop?
 *       - Marking upon push prevents duplicate pushes of the same vertex from multiple concurrent neighbors!
 * 
 * TIME COMPLEXITY:
 * - O(V + E): Every vertex is enqueued/dequeued once, and every edge is traversed once (or twice if undirected).
 * 
 * SPACE COMPLEXITY:
 * - O(V) auxiliary space for queue and visited array.
 */

#include <iostream>
#include <vector>
#include <queue>

std::vector<int> bfsOfGraph(int V, const std::vector<std::vector<int>>& adj) {
    std::vector<int> bfs;
    std::vector<bool> visited(V, false);
    std::queue<int> q;

    // Start BFS from vertex 0
    visited[0] = true;
    q.push(0);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        bfs.push_back(u);

        for (int v : adj[u]) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Mark visited immediately BEFORE enqueueing to prevent duplicate additions into the queue frontier.
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    return bfs;
}

int main() {
    int V = 5;
    std::vector<std::vector<int>> adj(V);
    adj[0] = {1, 2, 3};
    adj[1] = {};
    adj[2] = {4};
    adj[3] = {};
    adj[4] = {};

    std::vector<int> res = bfsOfGraph(V, adj);
    std::cout << "BFS Traversal: ";
    for (int x : res) std::cout << x << " ";
    std::cout << "\n"; // 0 1 2 3 4

    return 0;
}
