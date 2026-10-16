/**
 * Problem: Topological Sort (Kahn's BFS & DFS Approaches)
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In standard BFS/DFS, node ordering is arbitrary based on traversal order.
 * - Topological sorting requires a linear ordering of vertices such that for EVERY directed edge u -> v,
 *   vertex u appears before vertex v in the ordering.
 * - This ordering exists IF AND ONLY IF the directed graph is a Directed Acyclic Graph (DAG).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Kahn's Algorithm (In-degree BFS):
 *   1. Calculate the in-degree of all vertices.
 *   2. Push all vertices with `inDegree == 0` into a queue (these vertices have no prerequisites).
 *   3. Pop a vertex `u`, append it to the topological order list.
 *   4. For each neighbor `v` of `u`, decrement `inDegree[v]`.
 *   5. If `inDegree[v]` becomes 0, push `v` into the queue.
 *   6. If the count of processed vertices equals `V`, a valid topological order exists; otherwise, a cycle exists.
 * 
 * TIME COMPLEXITY:
 * - O(V + E): Each vertex and edge is processed once.
 * 
 * SPACE COMPLEXITY:
 * - O(V): In-degree array and BFS queue.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

// Kahn's Algorithm (BFS based)
std::vector<int> topoSortKahns(int V, std::vector<std::vector<int>>& adj) {
    std::vector<int> inDegree(V, 0);
    for (int u = 0; u < V; u++) {
        for (int v : adj[u]) {
            inDegree[v]++;
        }
    }

    std::queue<int> q;
    for (int i = 0; i < V; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    std::vector<int> topoOrder;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topoOrder.push_back(u);

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Decrement in-degree of neighbors; once a node has 0 unresolved prerequisites, it can be scheduled next.
        for (int v : adj[u]) {
            inDegree[v]--;
            if (inDegree[v] == 0) {
                q.push(v);
            }
        }
    }

    if ((int)topoOrder.size() != V) {
        return {}; // Cycle detected, topological sort not possible
    }
    return topoOrder;
}

// DFS based Topological Sort
void dfsTopo(int u, std::vector<std::vector<int>>& adj, std::vector<bool>& visited, std::stack<int>& st) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfsTopo(v, adj, visited, st);
        }
    }
    // All descendants are completely explored; push current node to stack
    st.push(u);
}

std::vector<int> topoSortDFS(int V, std::vector<std::vector<int>>& adj) {
    std::vector<bool> visited(V, false);
    std::stack<int> st;

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfsTopo(i, adj, visited, st);
        }
    }

    std::vector<int> topoOrder;
    while (!st.empty()) {
        topoOrder.push_back(st.top());
        st.pop();
    }
    return topoOrder;
}

int main() {
    int V = 6;
    std::vector<std::vector<int>> adj(V);
    adj[5].push_back(2);
    adj[5].push_back(0);
    adj[4].push_back(0);
    adj[4].push_back(1);
    adj[2].push_back(3);
    adj[3].push_back(1);

    std::vector<int> kahns = topoSortKahns(V, adj);
    std::cout << "Kahn's Topological Sort: ";
    for (int x : kahns) std::cout << x << " ";
    std::cout << "\n";

    std::vector<int> dfsResult = topoSortDFS(V, adj);
    std::cout << "DFS Topological Sort:    ";
    for (int x : dfsResult) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
